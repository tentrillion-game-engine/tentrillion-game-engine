#ifndef TENTRILLIONGAMEENGINE_TENVULKANDEVICE_HPP
#define TENTRILLIONGAMEENGINE_TENVULKANDEVICE_HPP

#include <cstdint>
#include <vector>
#include <volk.h>
#include <vulkan/vulkan_core.h>

/**
 * @brief This is a basic container for the VkDevice and it's ID.
 *
 */
struct m_tenvulkan_device {
	VkDevice vk_device;
	VkPhysicalDevice vk_physical_device;
	uint32_t vk_device_id;
};

/**
 * @brief Fetches the features for a specified VkPhysicalDevice.
 *
 * @param current_physical_device The VkPhysicalDevice to query the features.
 * for.
 * @return VkPhysicalDeviceFeatures2 The features of this physical device.
 */
inline VkPhysicalDeviceFeatures2
get_device_features(VkPhysicalDevice current_physical_device) {
	VkPhysicalDeviceFeatures2 vk_physical_device_features{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2};

	vkGetPhysicalDeviceFeatures2(current_physical_device,
								 &vk_physical_device_features);

	return vk_physical_device_features;
}

/**
 * @brief Fetches the properties for a specified VkPhysicalDevice.
 *
 * @param current_physical_device The VkPhysicalDevice to query the properties.
 * @return VkPhysicalDeviceProperties2 The properties of this physical device.
 */
inline VkPhysicalDeviceProperties2
get_device_properties(VkPhysicalDevice current_physical_device) {
	VkPhysicalDeviceProperties2 vk_physical_properties{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};

	vkGetPhysicalDeviceProperties2(current_physical_device,
								   &vk_physical_properties);
	return vk_physical_properties;
}

class tenvulkan;
class tenvulkan_queue;
class tenvulkan_device {
  public:
	explicit tenvulkan_device(tenvulkan *tenvulkan_pointer);
	~tenvulkan_device();

	/**
	 * This automatically selects the best device from the list. This should be
	 * only called once during the creation process.
	 */
	bool vk_create_device();

	/**
	 * This selects the device based on the ID that's given by the argument.
	 * This should only be called once during the creation process.
	 */
	bool vk_create_device(const int &device_id);

	/**
	 * @brief This destroys the primary Vulkan device.
	 *
	 */
	void destroy_vk_device();

  private:
	/**
	 * @brief Scans the available Vulkan devices.
	 *
	 */
	void scan_available_vk_devices();

	/**
	 * @brief
	 *
	 * @param id
	 */
	void m_create_device(const uint32_t &id);

	/**
	 * @brief Attempts to fetch the specified physical Vulkan device.
	 *
	 * @param device_id The ID of the device to fetch.
	 * @exception std::out_of_range This exception is thrown if the
	 * specified device ID is beyond the range of all the physical devices
	 * available.
	 * @return VkPhysicalDevice The fetched VkPhysicalDevice.
	 */
	VkPhysicalDevice fetch_vk_physical_device(const uint32_t &device_id);

	/**
	 * TenVulkan reference, must be passed down when constructing the
	 * tenvulkan_device constructor.
	 */
	tenvulkan *m_tenvulkan;

	/**
	 * @brief The current Vulkan Queue manager. This contains the data for the
	 * current Vulkan queues. They can be the graphics
	 *
	 */
	tenvulkan_queue *m_tenvulkan_queue;

	/**
	 * The current primary VkDevice.
	 */
	m_tenvulkan_device vk_primary_device;

	/**
	 * The current list of Vulkan PHYSICAL devices. This isn't a list for the
	 * VkDevice, the VkPhysicalDevice which are devices that are usable for
	 * rendering.
	 */
	std::vector<VkPhysicalDevice> vk_physical_devices;
};

#endif
