#ifndef TENTRILLIONGAMEENGINE_WINDOWSERVICE_H
#define TENTRILLIONGAMEENGINE_WINDOWSERVICE_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "math/vectorMath.hpp"
#include "tentrillionService.hpp"

#ifdef TENTRILLION_BACKEND_VULKAN
#include <vulkan/vulkan.hpp>
#endif

namespace TenTrillionGameEngine {

enum RenderingBackend { OPENGL, VULKAN, SOFTWARE };

class TENTRILLION_GAME_ENGINE_EXPORT RenderingService
	: public TenTrillionService {

	Vector windowSize{};

  protected:
	SDL_Window *windowInstance{};
	SDL_Renderer *rendererInstance{};

#ifdef TENTRILLION_BACKEND_VULKAN

	/**
	 * @brief The Vulkan Instance Extensions.
	 */
	unsigned int vkInstanceExtensionsCount{0};

	/**
	 * @brief The current VULKAN instance.
	 */
	VkInstance vkInstance{};

	/**
	 * @brief  The VULKAN surface that is being used. The TenTrillion Vulkan
	 * Backend uses its own surface and rendering logic compared to the other
	 * backends, which use SDL_Surface.
	 */
	VkSurfaceKHR vkSurfaceKhr{};

	/**
	 * @brief The Physical Device of the VULKAN instance.
	 */
	VkPhysicalDevice vkPhysicalDevice{};

	/**
	 * @brief Current VULKAN device of the TenTrillion.
	 */
	VkDevice vkDevice{};

	/**
	 * @brief The Vulkan Graphics Queue.
	 */
	VkQueue graphicsQueue{};

	/**
	 * @brief The Vulkan Presentation Queue.
	 */
	VkQueue presentQueue{};

#endif

  public:
	/**
	 *
	 */
	RenderingBackend backend;

	/**
	 * @brief Initialize the Rendering Service.
	 * @param windowSize The size of the window to set.
	 * @param windowTitle The caption of the window.
	 * @param engine The TenTrillionEngine reference.
	 */
	RenderingService(Vector windowSize, const char *windowTitle,
					 TentrillionEngine *engine);

#ifdef TENTRILLION_BACKEND_VULKAN
	/**
	 * @brief Create the VULKAN instance.
	 */
	void createVkInstance();

	/**
	 * @brief Create the VULKAN device responsible for the rendering.
	 */
	void createVkDevice();
#endif

	/**
	 * @brief This returns the current SDL window instance.
	 * @return The SDL window instance.
	 */
	[[nodiscard]] SDL_Window *getWindowInstance() const;

	[[nodiscard]] SDL_Renderer *getRendererInstance() const;
	void setRendererInstance(SDL_Renderer *m_rendererInstance);

	/**
	 * @brief This returns the window size of the current window.
	 * @return Window Size Vector.
	 */
	Vector &getWindowSize();

	/**
	 * @brief Quit the rendering service.
	 */
	void quitService() override;
};

} // namespace TenTrillionGameEngine

#endif // !TENTRILLIONGAMEENGINE_WINDOWSERVICE_H