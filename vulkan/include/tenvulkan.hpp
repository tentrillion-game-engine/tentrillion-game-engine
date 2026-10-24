#ifndef TENTRILLIONGAMEENGINE_TENVULKAN_HPP
#define TENTRILLIONGAMEENGINE_TENVULKAN_HPP

#include <cstdint>
#include <volk.h>
#include <vulkan/vulkan_core.h>

/**
 * @brief TenTrillion Game Engine TenVulkan/Vulkano VULKAN system.
 */
class tenvulkan {
  public:
	tenvulkan(const char *application_name,
			  const uint32_t &application_version);

	void vk_create_instance(const char *application_name,
							const uint32_t &application_version);
	~tenvulkan();

  private:
	VkApplicationInfo vk_app_info;
	VkInstanceCreateInfo vk_instance_info;
};

#endif
