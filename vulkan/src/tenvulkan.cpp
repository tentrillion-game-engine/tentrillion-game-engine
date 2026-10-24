#include "tenvulkan.hpp"
#include "GLFW/glfw3.h"
#include "tentrillion_constants.hpp"
#include <cstdint>
#include <vector>
#include <vulkan/vulkan_core.h>

tenvulkan::tenvulkan(const char *application_name,
					 const uint32_t &application_version) {
	this->vk_create_instance(application_name, application_version);
}

void tenvulkan::vk_create_instance(const char *application_name,
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

#define CHECK_VULKAN_EXTENSION()

#ifdef WIN32
			instance_extensions.push_back("VK_KHR_win32_surface");

#elif defined(__linux__) || defined(__gnu_linux__)
// TODO: Add specific extensions for Wayland and X11, plus acquiring the DRM
// surface.
#else
			instance_extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#endif

#ifdef __APPLE__
			instance_extensions.push_back(
				VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif
		}
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
}