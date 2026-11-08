#include "tenvulkan_device.hpp"
#include "tenvulkan.hpp"
#include <cstdint>
#include <stdexcept>
#include <vector>

tenvulkan_device::tenvulkan_device(class tenvulkan *tenvulkan_pointer) {
	if (tenvulkan_pointer == nullptr)
		throw new std::runtime_error("tenvulkan reference isn't defined.");

	this->m_tenvulkan = tenvulkan_pointer;

	// After the vulkan device manager is created, tell it to scan the available
	// devices.
	this->scan_available_vk_devices();
}

bool tenvulkan_device::vk_create_device() { return true; }
bool tenvulkan_device::vk_create_device(int device_id) { return true; }

void tenvulkan_device::scan_available_vk_devices() {
	// Tell the Vulkan driver to scan the available devices to find all of them
	// that the TenTrillion Game Engine can use.

	uint32_t device_count{0};
	vkEnumeratePhysicalDevices(this->m_tenvulkan->get_vk_instance(),
							   &device_count, nullptr);
	this->vk_physical_devices = std::vector<VkPhysicalDevice>(device_count);
	vkEnumeratePhysicalDevices(this->m_tenvulkan->get_vk_instance(),
							   &device_count, this->vk_physical_devices.data());
}
