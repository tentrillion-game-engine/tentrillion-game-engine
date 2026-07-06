

#ifndef TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP
#define TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP
#include "BaseService.hpp"

#include <TenTrillionGameEngineExport.h>
namespace TenTrillion {
/**
 * TenTrillion Vulkan API.
 * This is the Vulkan API accessor and wrapper for the TenTrillion.
 */
class TENTRILLIONGAMEENGINE_EXPORT Vulkano : BaseService {
  public:
	~Vulkano() override = default;
	explicit Vulkano(Main *engineReference) : BaseService(engineReference) {}

	void InitializeService() override;
	void DeInitializeService() override;
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_VULKANRENDERINGSERVICE_HPP
