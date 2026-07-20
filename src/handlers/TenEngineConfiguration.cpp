#include "handlers/TenEngineConfiguration.hpp"
#ifdef __linux__
#include <sys/stat.h>
#endif

namespace TenTrillion {

constexpr auto TenTrillionConfigurationFile = "tentrillion.tenconfig";

void TenEngineConfiguration::ImportEngineConfig() {
#ifdef __linux__
	struct stat buffer{};
	if (stat(TenTrillionConfigurationFile, &buffer) != 0 ||
		S_ISDIR(buffer.st_mode)) {
		throw std::runtime_error("engine configuration file not found");
	}

#endif
}
} // namespace TenTrillion