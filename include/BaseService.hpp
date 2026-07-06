

#ifndef TENTRILLIONGAMEENGINE_TENTRILLIONSERVICE_HPP
#define TENTRILLIONGAMEENGINE_TENTRILLIONSERVICE_HPP
#include <TenTrillionGameEngineExport.h>

namespace TenTrillion {
class Main;
class TENTRILLIONGAMEENGINE_EXPORT BaseService {

  public:
	virtual ~BaseService() = default;
	/**
	 * Base class for all TenTrillion Services.
	 */
	explicit BaseService(TenTrillion::Main *gameEngineReference) {
		this->GameEngine = gameEngineReference;
	};

	/**
	 * This returns the service name for this TenTrillion Service.
	 * @return Name of the Service.
	 */
	static const char *GetServiceName() { return "Default Service"; }
	/**
	 * This initializes this service, called by the main TenTrillion Game Engine
	 * class.
	 */
	virtual void InitializeService() {}
	/**
	 * This deinitializes the service, called by the main TenTrillion Game
	 * Engine class.
	 */
	virtual void DeInitializeService() {}

  protected:
	/**
	 * The reference to the TenTrillionGameEngine class.
	 */
	Main *GameEngine;
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_TENTRILLIONSERVICE_HPP
