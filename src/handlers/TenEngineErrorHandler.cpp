

#include "handlers/TenEngineErrorHandler.hpp"

#include "TenTrillionGameEngine.hpp"

#include <exception>

namespace TenTrillion {
void SetEngineErrorHandler() {
	std::set_terminate([] {
		const TenTrillionGameEngine *engineReference =
			TenTrillionGameEngine::GetEngineReference();
		TenRenderingService *renderingService =
			engineReference->GetRenderingService();

#ifdef __linux__

#endif

#ifdef WIN32

#endif
		std::abort();
	});
}
} // namespace TenTrillion