#ifndef TENTRILLIONGAMEENGINE_TENVULKANQUEUE_HPP
#define TENTRILLIONGAMEENGINE_TENVULKANQUEUE_HPP

#include <unordered_map>
#include <vector>
#include <volk.h>

class tenvulkan;
class tenvulkan_queue {
  public:
	explicit tenvulkan_queue(tenvulkan *tenvulkan);

	/**
	 * @brief
	 *
	 */
	enum class tenvulkan_queue_creation_result {
		GeometryShaderNotSupported = 0x000001,
		TargetedFlagNotSupported
	};

	/**
	 * @brief Attempt to create a Vulkan Queue Family.
	 *
	 * @param vk_physical_device The current Vulkan Physical Device, referenced
	 * by pointer.
	 * @param flag The Vulkan Queue Family flag that we're searching for.
	 * @return true If the Vulkan Queue family was successfully created and the
	 * tenvulkan device manager can PROCEED onwards.
	 * @return false If the Vulkan Queue Family wasn't able to get created.
	 */
	tenvulkan_queue_creation_result
	create_vk_queue(VkPhysicalDevice vk_physical_device, const int &flag,
					const float &queue_priority);

  private:
	tenvulkan *m_tenvulkan;

	/**
	 * @brief Attempts to get the queue family properties
	 *
	 * @param vk_physical_device
	 * @return VkQueueFamilyProperties2
	 */
	std::vector<VkQueueFamilyProperties2>
	get_physical_device_queue_family_properties(
		VkPhysicalDevice vk_physical_device) const;

	/**
	 * @brief The current Vulkan Queue Family set. The TenTrillion will
	 * create at least 2 Queue Families containing the usual graphics queue
	 * and the compute queue for compute shaders.
	 */
	std::unordered_map<int, VkQueue> queues;
};

#endif
