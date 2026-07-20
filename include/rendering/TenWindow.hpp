

#ifndef TENTRILLIONGAMEENGINE_TENWINDOW_HPP
#define TENTRILLIONGAMEENGINE_TENWINDOW_HPP
#include "GLFW/glfw3.h"
#include "additional/TenString.hpp"

namespace TenTrillion {
class TenRenderingService;
class TenWindow {
  public:
	/**
	 * Initialize the TenTrillion Windower.
	 * @param renderingService The pointer to the rendering service.
	 */
	explicit TenWindow(TenRenderingService *renderingService);

	/**
	 * This initializes the window context.
	 */
	void InitializeWindow();

	/**
	 * This terminates the window context.
	 */
	void TerminateWindow() const;

  private:
	/**
	 * The current window.
	 */
	GLFWwindow *window{nullptr};
	/**
	 * The pointer to the renderingService.
	 */
	TenRenderingService *renderingService{nullptr};
	/**
	 * The title of the TenTrillion Window.
	 */
	TenString windowTitle{"TenTrillion Window"};
	/**
	 * The width of the TenTrillion Window.
	 */
	int windowWidth{800};
	/**
	 * The height of the TenTrillion window.
	 */
	int windowHeight{600};
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_TENWINDOW_HPP
