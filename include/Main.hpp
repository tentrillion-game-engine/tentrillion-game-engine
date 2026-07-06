#ifndef TENTRILLION_GAME_ENGINE_HPP
#define TENTRILLION_GAME_ENGINE_HPP
#include "LoggingSystem.hpp"
#include "rendering/RenderingService.hpp"

#include <TenTrillionGameEngineExport.h>
#include <memory>

namespace TenTrillion {

class TENTRILLIONGAMEENGINE_EXPORT Main {
  protected:
	std::unique_ptr<RenderingService> renderingService{nullptr};
	LoggingSystem *loggingSystem{new LoggingSystem()};
	static Main *engineReference;

  public:
	// Initialize the TenTrillion Instance.
	void Initialize();
	// Initialize and create all the services in the engine.
	void InitializeAllServices();
	// De-Initialize the TenTrillion Instance.
	void DeInitialize();
	// Get the logging system of the TenTrillion.
	[[nodiscard]] LoggingSystem *GetLoggingSystem() const {
		return loggingSystem;
	}
	// Get the rendering system of the TenTrillion.
	[[nodiscard]] RenderingService *GetRenderingService() const {
		return renderingService.get();
	}
	// Get the reference to the Game Engine.
	[[nodiscard]] static Main *GetEngineReference() { return engineReference; }
	// The Error Callback for GLFW instances.
	static void GLFWErrorCallback(int error, const char *description) {
		LoggingSystem *loggingSystem = engineReference->GetLoggingSystem();
		loggingSystem->Log(LoggingSystem::ERROR, description);
		free(loggingSystem);
	}
};
} // namespace TenTrillion

#endif // TENTRILLION_GAME_ENGINE_HPP
