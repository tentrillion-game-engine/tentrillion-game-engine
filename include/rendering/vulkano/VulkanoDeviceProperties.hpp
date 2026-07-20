

#ifndef TENTRILLIONGAMEENGINE_VULKANODEVICEPROPERTIES_HPP
#define TENTRILLIONGAMEENGINE_VULKANODEVICEPROPERTIES_HPP

#include <vector>
#include <volk.h>

struct VulkanoDeviceProperties {
	/**
	 * The physical vulkan device.
	 */
	VkPhysicalDevice physicalDevice;
	/**
	 * The physical device's properties.
	 */
	VkPhysicalDeviceProperties physicalDeviceProperties;
	/**
	 * The properties containing this specific queue family.
	 */
	std::vector<VkQueueFamilyProperties> physicalDeviceQueueFamilyProperties;
};

#endif // TENTRILLIONGAMEENGINE_VULKANODEVICEPROPERTIES_HPP
