

#ifndef TENTRILLIONGAMEENGINE_TENTRILLIONRENDERING_HPP
#define TENTRILLIONGAMEENGINE_TENTRILLIONRENDERING_HPP

#include "TenWindow.hpp"

#include <TenBaseService.hpp>
#include <TenTrillionGameEngineExport.h>
#include <functional>

namespace TenTrillion {
class TenGL;
class Vulkano;
/**
 * This class is the rendering service class.
 * It allows the different rendering backends to be easily accessed through
 * here, as the initializer will reference the commands in the backend to
 * the specified function.
 */
class TENTRILLIONGAMEENGINE_EXPORT TenRenderingService : TenBaseService {
  public:
	/**
	 * The rendering backend enums for the TenTrillion.
	 */
	enum RenderingBackend { VULKAN, OPENGL, SOFTWARE, NO_RENDER };

	~TenRenderingService() override = default;
	explicit TenRenderingService(TenTrillionGameEngine *engineReference)
		: TenBaseService(engineReference) {}

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
	 * Get the current rendering service.
	 * @return Rendering Service.
	 */
	static TenRenderingService *GetRenderingService();

	/**
	 * Get a reference to the Rendering Backend that is currently being
	 * used.
	 * @return RenderingBackend
	 */
	RenderingBackend &GetRenderingBackend();

	/**
	 * Get the current TenWindow.
	 * @return TenWindow.
	 */
	[[nodiscard]] TenWindow *GetTenWindow() const;

  private:
	/**
	 * The current rendering service instance.
	 */
	static TenRenderingService *RenderingService;

	/**
	 * The current rendering backend.
	 */
	RenderingBackend renderingBackend{NO_RENDER};

	/**
	 * The vulkan rendering backend, nicknamed "Vulkano". Each instance is
	 * NOT initialized to memory at first, but the specified driver is then
	 * loaded later.
	 */
	Vulkano *vulkano{nullptr};

	/**
	 * The OpenGL rendering backend, nicknamed "TenGL". Each instance is NOT
	 * initialized to memory at first, but the specified driver is then
	 * loaded later.
	 */
	TenGL *tenGL{nullptr};

	/**
	 * This windowing system of the TenTrillion.
	 */
	TenWindow *tenWindow{nullptr};

	/**
	 * This creates the function pointer link that the Vulkano/Vulkan
	 * backend needs.
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
