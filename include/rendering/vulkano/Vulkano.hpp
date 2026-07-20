

#ifndef TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP
#define TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP

#include "TenBaseService.hpp"
#include "VulkanoDeviceManager.hpp"

#include <TenTrillionGameEngineExport.h>
#include <vector>
#include <volk.h>

#define VULKANO_TENTRILLION_NAME "TenTrillion Game Engine Vulkan PreProcessor\n"
#define VULKANO_TENTRILLION_NAME_ENGINE "TenTrillion Game Engine\n"

/**
 * Assert on VK_SUCCESS. This is meant for the LOADING FUNCTIONS ONLY.
 * @param macro The vulkan function to execute. If not VK_SUCCESS, terminate.
 */
#define VK_ASSERT(macro) assert(macro == VK_SUCCESS);

namespace TenTrillion {
/**
 * TenTrillion Vulkan API.
 * This is the Vulkan API accessor and wrapper for the TenTrillion.
 */
class TENTRILLIONGAMEENGINE_EXPORT Vulkano : TenBaseService {
  public:
	~Vulkano() override = default;
	explicit Vulkano(TenTrillionGameEngine *engineReference);

	void InitializeService() override;
	void DeInitializeService() override;

	/**
	 * Get the current Vulkan Instance.
	 * @return VkInstance
	 */
	[[nodiscard]] VkInstance GetVkInstance() const { return vkInstance; }

	/**
	 * Get the current instance version of Vulkan.
	 * @return Vulkan Instance Version.
	 */
	uint32_t &GetVulkanInstanceVersion() { return vulkanInstanceVersion; }

  private:
	VulkanoDeviceManager *vulkanDeviceManager{nullptr};

	/**
	 * Create the vulkan instance.
	 */
	void createVulkanInstance();

	/**
	 * The current vulkan instance of the game engine.
	 */
	VkInstance vkInstance{nullptr};

	/**
	 * The instance version of the Vulkan API.
	 */
	uint32_t vulkanInstanceVersion{0};

	/**
	 * The current Vulkan Extensions.
	 */
	const char **vulkanExtensions{nullptr};

	/**
	 * The current Vulkan extensions used by the engine.
	 */
	uint32_t vulkanExtensionsCount{0};
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP
