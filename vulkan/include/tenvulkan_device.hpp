#ifndef TENTRILLIONGAMEENGINE_TENVULKANDEVICE_HPP
#define TENTRILLIONGAMEENGINE_TENVULKANDEVICE_HPP

#include <cstdint>
#include <vector>
#include <volk.h>

/**
 * @brief This is a basic container for the VkDevice and it's ID.
 *
 */
struct m_tenvulkan_device {
	VkDevice vk_device;
	VkPhysicalDevice vk_physical_device;
	uint32_t vk_device_id;
};

class tenvulkan;
class tenvulkan_device {
  public:
	tenvulkan_device(tenvulkan *tenvulkan_pointer);
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

	/**
	 * @brief Get the properties of a specified GPU device through Vulkan.
	 *
	 * @param device_id The ID of the device to use.
	 * @return VkPhysicalDeviceProperties2 Properties of the device.
	 */
	VkPhysicalDeviceProperties2
	get_device_properties(const uint32_t &device_id);

  private:
	/**
	 * @brief Scans the available Vulkan devices.
	 *
	 */
	void scan_available_vk_devices();

	/**
	 * @brief Attempts to fetch the specified physical Vulkan device.
	 *
	 * @param device_id The ID of the device to fetch.
	 * @exception std::out_of_range This exception is thrown if the specified
	 * device ID is beyond the range of all the physical devices available.
	 * @return VkPhysicalDevice The fetched VkPhysicalDevice.
	 */
	VkPhysicalDevice
	fetch_current_vk_physical_device(const uint32_t &device_id);

	/**
	 * TenVulkan reference, must be passed down when constructing the
	 * tenvulkan_device constructor.
	 */
	tenvulkan *m_tenvulkan;

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
