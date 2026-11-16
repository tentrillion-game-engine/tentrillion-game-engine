#include "tenvulkan_queue.hpp"
#include "GLFW/glfw3.h"
#include "tenvulkan.hpp"
#include "tenvulkan_device.hpp"
#include <cstdint>
#include <vector>
#include <vulkan/vulkan_core.h>

tenvulkan_queue::tenvulkan_queue(tenvulkan *tenvulkan)
	: m_tenvulkan(tenvulkan) {}

tenvulkan_queue::tenvulkan_queue_creation_result
tenvulkan_queue::create_vk_queue(VkPhysicalDevice vk_physical_device,
								 const int &flag, const float &queue_priority) {
	VkPhysicalDeviceFeatures2 phys_features =
		get_device_features(vk_physical_device);
	auto properties =
		this->get_physical_device_queue_family_properties(vk_physical_device);

	if (!phys_features.features.geometryShader)
		return tenvulkan_queue_creation_result::GeometryShaderNotSupported;

	for (uint32_t i = 0; i < properties.size(); i++) {
		if (properties[i].queueFamilyProperties.queueFlags & flag &&
			glfwGetPhysicalDevicePresentationSupport(
				m_tenvulkan->get_vk_instance(), vk_physical_device, i)) {
			VkDeviceQueueCreateInfo vk_queue_create_info{
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.queueFamilyIndex = i,
				.queueCount = 1,
				.pQueuePriorities = &queue_priority};
			// TODO
		}
	}

	return tenvulkan_queue_creation_result::TargetedFlagNotSupported;
}

std::vector<VkQueueFamilyProperties2>
tenvulkan_queue::get_physical_device_queue_family_properties(
	VkPhysicalDevice vk_physical_device) const {
	uint32_t queue_family_count{0};
	vkGetPhysicalDeviceQueueFamilyProperties2(vk_physical_device,
											  &queue_family_count, nullptr);
	auto properties = std::vector<VkQueueFamilyProperties2>(queue_family_count);
	vkGetPhysicalDeviceQueueFamilyProperties2(
		vk_physical_device, &queue_family_count, properties.data());
	return properties;
}