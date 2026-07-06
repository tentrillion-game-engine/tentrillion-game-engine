

#ifndef TENTRILLIONGAMEENGINE_TENTRILLIONRENDERING_HPP
#define TENTRILLIONGAMEENGINE_TENTRILLIONRENDERING_HPP

#include <BaseService.hpp>
#include <TenTrillionGameEngineExport.h>
#include <functional>
#include <memory>

namespace TenTrillion {
class TenGL;
class Vulkano;
/**
 * This class is the rendering service class.
 * It allows the different rendering backends to be easily accessed through
 * here, as the initializer will reference the commands in the backend to the
 * specified function.
 */
class TENTRILLIONGAMEENGINE_EXPORT RenderingService : BaseService {
	enum RenderingBackend { VULKAN, OPENGL, SOFTWARE, NO_RENDER };

  public:
	~RenderingService() override = default;
	explicit RenderingService(Main *engineReference)
		: BaseService(engineReference) {}

	void InitializeService() override;
	void DeInitializeService() override;

	/**
	 * The function pointer to initializing the specified Rendering Backend
	 * Service.
	 */
	std::function<void()> InitializeRenderingBackend;

	/**
	 * The function pointer to initializing the specified Rendering Backend
	 * Service.
	 */
	std::function<void()> DeInitializeRenderingBackend;

	/**
	 * Get a reference to the Rendering Backend that is currently being used.
	 * @return RenderingBackend
	 */
	RenderingBackend &GetRenderingBackend();

  private:
	/**
	 * The current rendering backend.
	 */
	RenderingBackend renderingBackend{NO_RENDER};

	/**
	 * The vulkan rendering backend, nicknamed "Vulkano". Each instance is NOT
	 * initialized to memory at first, but the specified driver is then loaded
	 * later.
	 */
	Vulkano *vulkano{nullptr};

	/**
	 * The OpenGL rendering backend, nicknamed "TenGL". Each instance is NOT
	 * initialized to memory at first, but the specified driver is then loaded
	 * later.
	 */
	TenGL *tenGL{nullptr};

	/**
	 * This creates the function pointer link that the Vulkano/Vulkan backend
	 * needs.
	 */
	void createVulkanoPassthrough();

	/**
	 * This creates the function pointer link that the TenGL/OpenGL backend
	 * needs.
	 */
	void createTenGLPassthrough();
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_TENTRILLIONRENDERING_HPP
