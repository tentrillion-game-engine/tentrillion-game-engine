

#include "rendering/TenRenderingService.hpp"

#include "GLFW/glfw3.h"
#include "TenTrillionGameEngine.hpp"
#include "rendering/tengl/TenGL.hpp"
#include "rendering/vulkano/Vulkano.hpp"
#include "volk.h"

namespace TenTrillion {
void TenRenderingService::InitializeService() {
	this->tenWindow = new TenWindow(this);

	TenLoggingSystem *loggingSystem = this->GameEngine->GetLoggingSystem();
	this->renderingBackend = VULKAN;

	glfwSetErrorCallback(TenTrillionGameEngine::GLFWErrorCallback);
	if (!glfwInit()) {
		loggingSystem->Log(TenLoggingSystem::ERROR,
						   "Failed to initialize GLFW, Halting!");
		exit(1);
	}

	if (!(volkInitialize() == VK_SUCCESS && glfwVulkanSupported())) {
		loggingSystem->Log(
			TenLoggingSystem::WARNING,
			"Failed to initialize Vulkan, defaulting to OpenGL.");
		this->renderingBackend = OPENGL;
	}
	switch (this->renderingBackend) {
	case VULKAN:
		// Create the specified passthrough to the Vulkano API.
		this->vulkano = new Vulkano(this->GameEngine);
		this->createVulkanoPassthrough();
		break;
	case OPENGL:
		// Create the specified passthrough to the TenGL API.
		this->tenGL = new TenGL(this->GameEngine);
		this->createTenGLPassthrough();
		break;
	default:
		loggingSystem->Log(TenLoggingSystem::ERROR, "");
		exit(2);
	}
	this->InitializeRenderingBackend();
	this->tenWindow->InitializeWindow();
}

// These are for keeping the engine beginner-friendly, but also easily
// controllable too.

void TenRenderingService::createVulkanoPassthrough() {
	// Each one for the vulkan functions are referenced here and are
	// created.
	this->InitializeRenderingBackend = [&] { vulkano->InitializeService(); };
	this->DeInitializeRenderingBackend = [&] {
		vulkano->DeInitializeService();
	};
}

void TenRenderingService::createTenGLPassthrough() {
	// Each one for the OpenGL functions are referenced here and created.
	this->InitializeRenderingBackend = [&] { tenGL->InitializeService(); };
	this->DeInitializeRenderingBackend = [&] { tenGL->DeInitializeService(); };
}
TenRenderingService::RenderingBackend &
TenRenderingService::GetRenderingBackend() {
	return this->renderingBackend;
}
TenWindow *TenRenderingService::GetTenWindow() const { return this->tenWindow; }

void TenRenderingService::DeInitializeService() {
	// Free up the remaining memory to keep performance.
	free(this->tenWindow);
	free(this->vulkano);
	free(this->tenGL);
}
}; // namespace TenTrillion