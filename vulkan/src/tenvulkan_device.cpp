#include "tenvulkan_device.hpp"
#include "tentrillion_constants.hpp"
#include "tenvulkan.hpp"
#include "tenvulkan_errors.hpp"
#include <cstdint>
#include <stdexcept>
#include <vector>

tenvulkan_device::tenvulkan_device(class tenvulkan *tenvulkan_pointer) {
	if (tenvulkan_pointer == nullptr)
		throw tentrillion_reference_is_null(
			"tenvulkan reference isn't defined.");

	this->m_tenvulkan = tenvulkan_pointer;

	// After the vulkan device manager is created, tell it to scan the available
	// devices.
	this->scan_available_vk_devices();
}

tenvulkan_device::~tenvulkan_device() = default;

bool tenvulkan_device::vk_create_device() { return true; }
bool tenvulkan_device::vk_create_device(const int &device_id) {
	// TODO
	return true;
}

VkPhysicalDevice
tenvulkan_device::fetch_vk_physical_device(const uint32_t &device_id) {
	if (!TENTRILLION_RANGE_CHECK(device_id, 0,
								 this->vk_physical_devices.size()))
		throw std::out_of_range("selected device that is not in range!");

	return this->vk_physical_devices[device_id];
}

void tenvulkan_device::scan_available_vk_devices() {
	// Tell the Vulkan driver to scan the available devices to find all of
	// them that the TenTrillion Game Engine can use.

	uint32_t device_count{0};
	VkInstance vk_instance = this->m_tenvulkan->get_vk_instance();

	vkEnumeratePhysicalDevices(vk_instance, &device_count, nullptr);
	this->vk_physical_devices = std::vector<VkPhysicalDevice>(device_count);
	vkEnumeratePhysicalDevices(vk_instance, &device_count,
							   this->vk_physical_devices.data());
}
