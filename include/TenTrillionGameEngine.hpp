#ifndef TENTRILLION_GAME_ENGINE_HPP
#define TENTRILLION_GAME_ENGINE_HPP
#include "handlers/TenLoggingSystem.hpp"
#include "rendering/TenRenderingService.hpp"

#include <TenTrillionGameEngineExport.h>
#include <memory>

/**
 * The general namespace for the TenTrillion Game Engine.
 */
namespace TenTrillion {

class TENTRILLIONGAMEENGINE_EXPORT TenTrillionGameEngine {
  protected:
	TenRenderingService *renderingService{nullptr};

	TenLoggingSystem *loggingSystem{new TenLoggingSystem()};
	static TenTrillionGameEngine *engineReference;

  public:
	/**
	 * Initializes the engine.
	 */
	void Initialize();
	/**
	 * Initialize all services.
	 */
	void InitializeAllServices();
	/**
	 * De-Initialize the engine.
	 */
	void DeInitialize();
	/**
	 * Get the LoggingSystem's pointer.
	 * @return LoggingSystem Pointer.
	 */
	[[nodiscard]] TenLoggingSystem *GetLoggingSystem() const {
		return loggingSystem;
	}
	/**
	 * Get the RenderingService's pointer.
	 * @return RenderingService's Pointer.
	 */
	[[nodiscard]] TenRenderingService *GetRenderingService() const {
		return renderingService;
	}
	/**
	 * Get the engine's main pointer.
	 * @return Main's pointer.
	 */
	[[nodiscard]] static TenTrillionGameEngine *GetEngineReference() {
		return engineReference;
	}
	/**
	 * The GLFW Error Callback, when GLFW encounters a critical error.
	 * @param error The error omitted.
	 * @param description The description of the error.
	 */
	static void GLFWErrorCallback(int error, const char *description) {
		TenLoggingSystem *loggingSystem = engineReference->GetLoggingSystem();
		loggingSystem->Log(TenLoggingSystem::ERROR, description);
	}
};
} // namespace TenTrillion

#endif // TENTRILLION_GAME_ENGINE_HPP
