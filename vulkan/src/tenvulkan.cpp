#include "tenvulkan.hpp"
#include "tentrillion_constants.hpp"
#include "tenvulkan_device.hpp"
#include "tenvulkan_queue.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <tuple>
#include <vector>

#ifdef __linux__

// This makes it so the Linux Kernel's DRM layer can be easily talked to.
#define VK_KHR_DRM_EXTENSION_NAME "VK_EXT_acquire_drm_display"

// This makes it so X11's control over the game window is released.
#define VK_KHR_DRM_X11_EXTENSION_NAME "VK_EXT_acquire_xlib_display"

#endif

tenvulkan::tenvulkan(const char *application_name,
					 const uint32_t &application_version) {
	this->tenvulkan_device_manager = new class tenvulkan_device(this);
	this->tenvulkan_queue =
		new class tenvulkan_queue(this->tenvulkan_device_manager);
}

tenvulkan::~tenvulkan() {
	// Cleanup:
	// Firstly, tell the TenVulkan Queue to get destroyed, then destroy the
	// devices.

	std::free(this->tenvulkan_queue);
	std::free(this->tenvulkan_device_manager);

	vkDestroyInstance(this->vk_instance, nullptr);
}

bool check_extension(
	std::vector<VkExtensionProperties> &vk_extension_properties,
	const char ext_name[256]) {
	return std::find_if_not(
			   vk_extension_properties.begin(), vk_extension_properties.end(),
			   [&ext_name](
				   const VkExtensionProperties &vk_extension_properties) {
				   return strcmp(vk_extension_properties.extensionName,
								 ext_name);
			   }) != vk_extension_properties.end();
}

bool tenvulkan::vk_create_instance(const char *application_name,
								   const uint32_t &application_version) {
	this->vk_app_info =
		VkApplicationInfo{.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
						  .pApplicationName = application_name,
						  .applicationVersion = application_version,
						  .pEngineName = TENTRILLION_INTERNAL_CODENAME,
						  .engineVersion = VK_MAKE_VERSION(0, 0, 1),
						  .apiVersion = VK_API_VERSION_1_3};

	std::vector<const char *> instance_extensions;

	uint32_t extension_count{0};
	if (vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
											   nullptr) != VK_SUCCESS) {
		auto vk_extension_properties =
			std::vector<VkExtensionProperties>(extension_count);
		if (vkEnumerateInstanceExtensionProperties(
				nullptr, &extension_count, vk_extension_properties.data()) !=
			VK_SUCCESS) {

#ifdef __linux__
			if (this->is_acquire_drm != tenvulkan_drm_control::NoControl) {

				if (auto [is_drm, is_x11_drm] =
						std::tuple{
							check_extension(vk_extension_properties,
											VK_KHR_DRM_EXTENSION_NAME),
							check_extension(vk_extension_properties,
											VK_KHR_DRM_X11_EXTENSION_NAME)};
					!(is_drm || is_x11_drm)) {
					this->is_acquire_drm = tenvulkan_drm_control::NoControl;
				} else {
					if (this->is_acquire_drm ==
							tenvulkan::tenvulkan_drm_control::
								X11DisplayControl &&
						strcmp(std::getenv("XDG_SESSION_TYPE"), "wayland") ==
							0) {
						// If the current session is detected as Wayland, do not
						// use the declining in functionality X11 extension.
						// For all the other old timers using X11, this
						// extension will still be supported.

						this->is_acquire_drm =
							tenvulkan::tenvulkan_drm_control::
								DirectRenderingManagerControl;
					}

					switch (this->is_acquire_drm) {
					case tenvulkan::tenvulkan_drm_control::
						DirectRenderingManagerControl:
						instance_extensions.push_back(
							VK_KHR_DRM_EXTENSION_NAME);
						break;
					case tenvulkan::tenvulkan_drm_control::X11DisplayControl:
						instance_extensions.push_back(
							VK_KHR_DRM_X11_EXTENSION_NAME);
						break;
					default:
						break;
					}
				}
			}

#endif
			instance_extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#ifdef __APPLE__
			instance_extensions.push_back(
				VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif
		}
	} else {
		return false;
	}

	this->vk_instance_info = VkInstanceCreateInfo{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
#ifdef __APPLE__
		.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
#endif
		.pApplicationInfo = &this->vk_app_info,
		.enabledExtensionCount =
			static_cast<uint32_t>(instance_extensions.size())

	};

	vkCreateInstance(&this->vk_instance_info, nullptr, &this->vk_instance);

	// Load the Vulkan instance with Volk. This is meant for compatibility and
	// doesn't really involve optimization.
	volkLoadInstance(this->vk_instance);

	return true;
}
