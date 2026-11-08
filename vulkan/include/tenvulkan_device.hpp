#ifndef TENTRILLIONGAMEENGINE_TENVULKANDEVICE_HPP
#define TENTRILLIONGAMEENGINE_TENVULKANDEVICE_HPP

#include <vector>
#include <volk.h>
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
	bool vk_create_device(int device_id);

  private:
	void scan_available_vk_devices();

	/**
	 * TenVulkan reference, must be passed down when constructing the
	 * tenvulkan_device constructor.
	 */
	tenvulkan *m_tenvulkan;

	/**
	 * The current primary VkDevice.
	 */
	VkDevice vk_primary_device;

	/**
	 * The current list of Vulkan PHYSICAL devices. This isn't a list for the
	 * VkDevice, the VkPhysicalDevice which are devices that are usable for
	 * rendering.
	 */
	std::vector<VkPhysicalDevice> vk_physical_devices;
};

#endif
