#include "tenvulkan_queue.hpp"
#include "tenvulkan_device.hpp"
#include "tenvulkan_errors.hpp"

tenvulkan_queue::tenvulkan_queue(tenvulkan_device *tenvulkan_device_manager) {
	if (tenvulkan_device_manager == nullptr)
		throw tentrillion_reference_is_null(
			"tenvulkan device manager reference isn't defined.");

	this->tenvulkan_device_manager = tenvulkan_device_manager;
}
