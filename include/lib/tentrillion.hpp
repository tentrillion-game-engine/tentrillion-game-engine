#ifndef TENTRILLIONGAMEENGINE_TENTRILLION_H

#include "services/renderingService.hpp"

#include <map>
#include <memory>
#include <tentrillion_export.h>

/**
 * THE TENTRILLION GAME ENGINE RETURN CODES
 * 2 -> FAILURE INITIALIZING RENDERER
 */

/**
 * This is the TenTrillion Game Engine namespace.
 */
namespace TenTrillionGameEngine {

class TENTRILLION_GAME_ENGINE_EXPORT TentrillionEngine {
  protected:
	/**
	 * The current rendering Service.
	 */
	std::unique_ptr<RenderingService> renderingService;
	/**
	 * The current TenTrillion Instance.
	 */
	static TentrillionEngine *tenTrillionInstance;

  public:
	/**
	 * Constructor for the TenTrillion Game Engine Functions.
	 */
	TentrillionEngine();
	/**
	 * This initializes the TenTrillion Instance.
	 * @param windowSize The Window Size for the engine to use.
	 * @param windowTitle The Window Caption for the engine to use.
	 */
	void initializeInstance(Vector windowSize, const char *windowTitle);
	/**
	 * This retrieves the current TenTrillion Instance.
	 * @return The TenTrillion Instance Ptr.
	 */
	static TentrillionEngine *getTenTrillionInstance();

	/**
	 * This retrieves the TenTrillion Information.
	 */
	static void displayTenTrillionInformation();

	/**
	 * This exits the TenTrillion Instance.
	 */
	void exitInstance() const;
};
} // namespace TenTrillionGameEngine
#endif // !TENTRILLIONGAMEENGINE_TENTRILLION_H