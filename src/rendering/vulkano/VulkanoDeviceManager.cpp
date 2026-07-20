

#include "rendering/vulkano/VulkanoDeviceManager.hpp"

#include "rendering/vulkano/Vulkano.hpp"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <stdexcept>
#include <volk.h>

namespace TenTrillion {
VulkanoDeviceManager::VulkanoDeviceManager(Vulkano *vulkano) {
	this->vulkano = vulkano;
}

void VulkanoDeviceManager::CreatePhysicalDevices() {

	// Firstly, get the number of physical devices available.
	uint32_t deviceCount{0};

	const auto vkInstance = vulkano->GetVkInstance();

	VK_ASSERT(vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr));
	auto physicalDevices = std::vector<VkPhysicalDevice>(deviceCount);
	VK_ASSERT(vkEnumeratePhysicalDevices(vkInstance, &deviceCount,
										 physicalDevices.data()))

	// NOTE: This is for shortening purposes only.
	std::function<VkPhysicalDeviceProperties(int index)> vkGetterFunction{};

	// Shorten the process of calling the Vulkan API for device properties.
	// The 1.0 version of the Vulkan API has different ways of calling the
	// vkGetPhysicalDeviceProperties command, So keep that in mind!
	if (vulkano->GetVulkanInstanceVersion() != VK_API_VERSION_1_0) {
		// The current most updated version of fetching the device properties
		// for the Vulkan API.
		vkGetterFunction = [&physicalDevices](const int index) {
			VkPhysicalDeviceProperties2 properties2{};
			vkGetPhysicalDeviceProperties2(physicalDevices[index],
										   &properties2);

			return properties2.properties;
		};
	} else {
		// The legacy method of fetching the device properties for the Vulkan
		// API.

		vkGetterFunction = [&physicalDevices](const int index) {
			VkPhysicalDeviceProperties properties{};
			vkGetPhysicalDeviceProperties(physicalDevices[index], &properties);

			return properties;
		};
	}

	// Query all the graphics processors and execute the specified getter action
	// for all of them.
	for (int i = 0; i < deviceCount; i++) {
		const auto physicalDevice = physicalDevices[i];
		const auto physicalDeviceProperties = vkGetterFunction(i);

		// This function, also has different definitions for each Vulkan
		// version different to 1.0.
		if (vulkano->GetVulkanInstanceVersion() != VK_API_VERSION_1_0) {
			// The Vulkan Developers recommend using this new method, so to
			// preserve the TenTrillion for the future, it has been used.

			uint32_t queueFamilyCount{0};
			vkGetPhysicalDeviceQueueFamilyProperties2(
				physicalDevice, &queueFamilyCount, nullptr);

			std::vector<VkQueueFamilyProperties2> queueFamilyProperties(
				queueFamilyCount);

			// Retrieve all the queue data for the Vulkano API.
			vkGetPhysicalDeviceQueueFamilyProperties2(
				physicalDevice, &queueFamilyCount,
				queueFamilyProperties.data());

			std::vector<VkQueueFamilyProperties> familyProperties(
				queueFamilyCount);

			// Transform the sequence into the queueFamilyProperties, only
			// grabbing the specified thing we need.
			std::transform(
				queueFamilyProperties.begin(), queueFamilyProperties.end(),
				std::back_inserter(familyProperties),
				[](const VkQueueFamilyProperties2 &deviceProperties2) {
					return deviceProperties2.queueFamilyProperties;
				});

			this->deviceProperties.emplace_back(VulkanoDeviceProperties{
				.physicalDevice = physicalDevice,
				.physicalDeviceProperties = physicalDeviceProperties,
				.physicalDeviceQueueFamilyProperties = std::move(
					familyProperties)} // To preserve speed and memory, the
									   // engine will not copy this value.
			);
		} else {
			// This is for the older legacy Vulkan platforms, that run on Vulkan
			// version 1.0.
			uint32_t queueFamilyCount{0};

			vkGetPhysicalDeviceQueueFamilyProperties(
				physicalDevice, &queueFamilyCount, nullptr);

			std::vector<VkQueueFamilyProperties> familyProperties(
				queueFamilyCount);

			vkGetPhysicalDeviceQueueFamilyProperties(
				physicalDevice, &queueFamilyCount, familyProperties.data());

			this->deviceProperties.emplace_back(VulkanoDeviceProperties{
				.physicalDevice = physicalDevice,
				.physicalDeviceProperties = physicalDeviceProperties,
				.physicalDeviceQueueFamilyProperties =
					std::move(familyProperties)});
		}
	}

	// If there's only one Vulkan device, skip the sorting process where the
	// engine searches for the GPU with the best results.
	if (this->deviceProperties.size() != 1) {
		// Sort based on the best vulkan device found.
		std::sort(
			this->deviceProperties.begin(), this->deviceProperties.end(),
			[](const VulkanoDeviceProperties &first,
			   const VulkanoDeviceProperties &second) {
				// These are the general comparisons the TenTrillion will
				// do before the Vulkan renderer is initialized. This part
				// of the code SHOULD be called only once, not frame by
				// frame!
				return
					// Check the frameBuffer width.
					first.physicalDeviceProperties.limits.maxFramebufferWidth <
						second.physicalDeviceProperties.limits
							.maxFramebufferWidth &&
					// Check the frameBuffer height.
					first.physicalDeviceProperties.limits.maxFramebufferHeight <
						second.physicalDeviceProperties.limits
							.maxFramebufferHeight &&
					// Check the maxCull distance.
					first.physicalDeviceProperties.limits.maxCullDistances <
						second.physicalDeviceProperties.limits.maxCullDistances;
			});
	}

	// One last safeguard check to prevent crashes.
	if (this->deviceProperties.empty()) {
		throw std::runtime_error(
			"no vulkan physical devices could be retrieved");
	}

	// Select the best physical device and add it.
	this->bestPhysicalDevice = this->deviceProperties[0];
}

void VulkanoDeviceManager::SelectVulkanDevice() {
	this->CreatePhysicalDevices();

	// TODO: Create vkDevice!
}
} // namespace TenTrillion