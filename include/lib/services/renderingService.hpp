#ifndef TENTRILLIONGAMEENGINE_WINDOWSERVICE_H
#define TENTRILLIONGAMEENGINE_WINDOWSERVICE_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "math/vectorMath.hpp"
#include "tentrillionService.hpp"

#include <functional>
#include <memory>
namespace TenTrillionGameEngine {

enum RenderingBackend { OPENGL, VULKAN, SOFTWARE };

class TENTRILLION_GAME_ENGINE_EXPORT RenderingService
	: public TenTrillionService {

	Vector windowSize{};

  protected:
	SDL_Window *windowInstance{};
	SDL_Renderer *rendererInstance{};

  public:
	/**
	 *
	 */
	RenderingBackend backend;

	/**
	 * Initialize the Rendering Service.
	 * @param windowSize The size of the window to set.
	 * @param windowTitle The caption of the window.
	 * @param engine The TenTrillionEngine reference.
	 */
	RenderingService(Vector windowSize, const char *windowTitle,
					 TentrillionEngine *engine);

	/**
	 * This returns the current SDL window instance.
	 * @return The SDL window instance.
	 */
	[[nodiscard]] SDL_Window *getWindowInstance() const;

	[[nodiscard]] SDL_Renderer *getRendererInstance() const;
	void setRendererInstance(SDL_Renderer *m_rendererInstance);

	/**
	 * This returns the window size of the current window.
	 * @return Window Size Vector.
	 */
	Vector &getWindowSize();

	/**
	 * Quit the rendering service.
	 */
	void quitService() override;
};

} // namespace TenTrillionGameEngine

#endif // !TENTRILLIONGAMEENGINE_WINDOWSERVICE_H