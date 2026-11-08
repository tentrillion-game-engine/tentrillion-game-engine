#ifndef TENTRILLIONGAMEENGINE_TENVULKAN_HPP
#define TENTRILLIONGAMEENGINE_TENVULKAN_HPP

#include "tenvulkan_device.hpp"
#include "tenvulkan_queue.hpp"
#include <cstdint>
#include <memory>
#include <volk.h>

/**
 * @brief TenTrillion Game Engine TenVulkan/Vulkano VULKAN system.
 */
class tenvulkan {

  public:
	enum tenvulkan_drm_control {
		NoControl,
		DirectRenderingManagerControl,
		X11DisplayControl
	};

	tenvulkan();

	bool vk_create_instance(const char *application_name,
							const uint32_t &application_version);

	~tenvulkan();

	VkInstance &get_vk_instance() { return this->vk_instance; }

#ifdef __linux__
	// Sets if the TenTrillion should acquire the current DRM display.
	// This will be make the TenTrillion faster, but should be specified by the
	// application in use case.
	void set_is_acquire_drm(const tenvulkan::tenvulkan_drm_control &is_acquire);
#endif

  private:
	/**
	 * This selects the specified Vk Extensions to be used for the specified
	 * system.
	 *
	 * @param vk_extension_properties The VkExtensionProperties that contain all
	 * the current extension properties.
	 * @param instance_extensions The current instance extensions that the
	 * engine is planning to create.
	 */
	void vk_select_extensions(
		std::vector<VkExtensionProperties> &vk_extension_properties,
		std::vector<const char *> &instance_extensions);

	/**
	 * The current Vulkan device manager. (VkDevice)
	 */
	std::unique_ptr<tenvulkan_device> tenvulkan_device_manager;

	/**
	 * The current Vulkan Queue manager. (VkQueue)
	 */
	std::unique_ptr<tenvulkan_queue> tenvulkan_queue_manager;

	/**
	 * The application information for the Vulkan implementation.
	 */
	VkApplicationInfo vk_app_info;

	/**
	 * This is the information about the Vulkan creation.
	 */
	VkInstanceCreateInfo vk_instance_info;

	/**
	 * The current Vulkan Instance.
	 */
	VkInstance vk_instance;

#ifdef __linux__
	// Flag for if the TenTrillion should acquire the DRM display and takeover
	// the current windowing manager.
	tenvulkan::tenvulkan_drm_control is_acquire_drm{
		tenvulkan_drm_control::NoControl};
#endif
};

#endif
