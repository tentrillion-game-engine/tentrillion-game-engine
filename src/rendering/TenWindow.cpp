#include "rendering/TenWindow.hpp"

#include "GLFW/glfw3.h"
#include "rendering/TenRenderingService.hpp"

namespace TenTrillion {
TenWindow::TenWindow(TenRenderingService *renderingService) {
	this->renderingService = renderingService;
}

void TenWindow::InitializeWindow() {
	if (this->renderingService->GetRenderingBackend() ==
		TenRenderingService::VULKAN) {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	this->window =
		glfwCreateWindow(this->windowWidth, this->windowHeight,
						 this->windowTitle.getCString(), nullptr, nullptr);
}

void TenWindow::TerminateWindow() const {
	glfwDestroyWindow(this->window);
	glfwTerminate();
}
} // namespace TenTrillion