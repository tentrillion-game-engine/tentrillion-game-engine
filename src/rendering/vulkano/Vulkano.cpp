

#include "rendering/vulkano/Vulkano.hpp"

#include "volk.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cassert>
#include <stdexcept>
#include <vector>

namespace TenTrillion {

Vulkano::Vulkano(TenTrillionGameEngine *engineReference)
	: TenBaseService(engineReference) {
	// Create the vulkano device manager.
	this->vulkanDeviceManager = new VulkanoDeviceManager(this);
}

void Vulkano::InitializeService() {
	this->createVulkanInstance();

	// Select the current Vulkan device.
	vulkanDeviceManager->SelectVulkanDevice();
}
void Vulkano::DeInitializeService() {
	vkDestroyInstance(this->vkInstance, nullptr);
	volkFinalize();

	// Free the remaining extensions and device properties.
	free(this->vulkanExtensions);
	free(this->vulkanDeviceManager);
}

void Vulkano::createVulkanInstance() {
	VkApplicationInfo vulkanoInformation{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = VULKANO_TENTRILLION_NAME,
		.pEngineName = VULKANO_TENTRILLION_NAME_ENGINE,
	};

	this->vulkanExtensions =
		glfwGetRequiredInstanceExtensions(&this->vulkanExtensionsCount);

	// Unfortunately, MacOS support requires a special Vulkan Extension to be
	// work.
#ifdef __APPLE__
	std::vector instanceExtensions(requiredInstanceExtensions,
								   requiredInstanceExtensions +
									   this->vulkanExtensionsCount);
	// MacOS support requires the portability enumeration to be pushed.
	instanceExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	this->vulkanExtensionsCount =
		static_cast<uint32_t>(instanceExtensions.size());
#endif

	// Create the vulkan Instance.
	const VkInstanceCreateInfo createInfo{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
		.pApplicationInfo = &vulkanoInformation,
		.enabledExtensionCount = this->vulkanExtensionsCount,
		.ppEnabledExtensionNames = this->vulkanExtensions};

	VK_ASSERT(vkCreateInstance(&createInfo, nullptr, &this->vkInstance));
	VK_ASSERT(vkEnumerateInstanceVersion(&this->vulkanInstanceVersion));
	volkLoadInstance(this->vkInstance);
}
} // namespace TenTrillion