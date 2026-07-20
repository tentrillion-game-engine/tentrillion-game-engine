

#ifndef TENTRILLIONGAMEENGINE_ENGINECONFIGURATION_HPP
#define TENTRILLIONGAMEENGINE_ENGINECONFIGURATION_HPP
#include <TenTrillionGameEngineExport.h>
#include <nlohmann/json.hpp>

namespace TENTRILLIONGAMEENGINE_EXPORT TenTrillion {
/**
 * To make the TenTrillion extremely easy for modders,
 * This is the EngineConfiguration API.
 * All the settings for the engine are stored locally for each game, in
 * tentrillion.json.
 */
class TenEngineConfiguration {
  public:
	TenEngineConfiguration() = default;

	/**
	 * Import the local engine configuration file.
	 */
	void ImportEngineConfig();

  private:
	/**
	 * The current config of the engine.
	 */
	nlohmann::json importedConfig;
};
} // namespace TENTRILLIONGAMEENGINE_EXPORT TenTrillion

#endif // TENTRILLIONGAMEENGINE_ENGINECONFIGURATION_HPP
