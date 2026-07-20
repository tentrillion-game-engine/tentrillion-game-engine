

#ifndef TENTRILLIONGAMEENGINE_VULKANODEVICEMANAGER_HPP
#define TENTRILLIONGAMEENGINE_VULKANODEVICEMANAGER_HPP
#include "VulkanoDeviceProperties.hpp"

#include <vector>
#include <volk.h>

namespace TenTrillion {
class Vulkano;
class VulkanoDeviceManager {
  public:
	explicit VulkanoDeviceManager(Vulkano *vulkano);

	/**
	 * Select the Vulkan device for usage.
	 */
	void SelectVulkanDevice();

  private:
	/**
	 * The Vulkano instance, passed down by the pointer reference.
	 */
	Vulkano *vulkano;

	/**
	 * The current vulkan device of the game engine.
	 */
	VkDevice vkDevice{nullptr};

	/**
	 * The properties of the Vulkan Physical Device.
	 * This is legacy!
	 */
	std::vector<VulkanoDeviceProperties> deviceProperties{};

	/**
	 * The best performing physical device.
	 */
	VulkanoDeviceProperties bestPhysicalDevice{};

	/**
	 * Create the physical devices needed for the TenTrillion's Vulkan System.
	 */
	void CreatePhysicalDevices();
};
} // namespace TenTrillion
#endif // TENTRILLIONGAMEENGINE_VULKANODEVICEMANAGER_HPP
