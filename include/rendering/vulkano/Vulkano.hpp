

#ifndef TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP
#define TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP

#include "TenBaseService.hpp"
#include <volk.h>

#include <TenTrillionGameEngineExport.h>
namespace TenTrillion {
/**
 * TenTrillion Vulkan API.
 * This is the Vulkan API accessor and wrapper for the TenTrillion.
 */
class TENTRILLIONGAMEENGINE_EXPORT Vulkano : TenBaseService {
  public:
	~Vulkano() override = default;
	explicit Vulkano(TenTrillionGameEngine *engineReference)
		: TenBaseService(engineReference) {}

	void InitializeService() override;
	void DeInitializeService() override;

  private:
	/**
	 * The current vulkan instance of the game engine.
	 */
	VkInstance vkInstance{nullptr};
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP
