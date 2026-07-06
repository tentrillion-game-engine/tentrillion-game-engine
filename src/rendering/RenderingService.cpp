

#include "rendering/RenderingService.hpp"

#include "GLFW/glfw3.h"
#include "Main.hpp"
#include "rendering/tengl/TenGL.hpp"
#include "rendering/vulkano/Vulkano.hpp"
#include "volk.h"

namespace TenTrillion {
void RenderingService::InitializeService() {
	LoggingSystem *loggingSystem = this->GameEngine->GetLoggingSystem();
	this->renderingBackend = VULKAN;

	glfwSetErrorCallback(Main::GLFWErrorCallback);
	if (!glfwInit()) {
		loggingSystem->Log(LoggingSystem::ERROR,
						   "Failed to initialize GLFW, Halting!");
		exit(1);
	}

	if (!(volkInitialize() == VK_SUCCESS && glfwVulkanSupported())) {
		loggingSystem->Log(
			LoggingSystem::WARNING,
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
		loggingSystem->Log(LoggingSystem::ERROR, "");
		exit(2);
	}
}

// These are for keeping the engine beginner-friendly, but also easily
// controllable too.

void RenderingService::createVulkanoPassthrough() {
	// Each one for the vulkan functions are referenced here and are
	// created.
	this->InitializeRenderingBackend = [&] { vulkano->InitializeService(); };
	this->DeInitializeRenderingBackend = [&] {
		vulkano->DeInitializeService();
	};
}

void RenderingService::createTenGLPassthrough() {
	// Each one for the OpenGL functions are referenced here and created.
	this->InitializeRenderingBackend = [&] { tenGL->InitializeService(); };
	this->DeInitializeRenderingBackend = [&] { tenGL->DeInitializeService(); };
}
RenderingService::RenderingBackend &RenderingService::GetRenderingBackend() {
	return this->renderingBackend;
}

void RenderingService::DeInitializeService() {
	// Free up the remaining memory to keep performance.
	free(this->vulkano);
	free(this->tenGL);
}
}; // namespace TenTrillion