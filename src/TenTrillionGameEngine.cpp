#include "TenTrillionGameEngine.hpp"

#include "handlers/TenEngineErrorHandler.hpp"

#include <rendering/TenRenderingService.hpp>

#include <volk.h>

TenTrillion::TenTrillionGameEngine
	*TenTrillion::TenTrillionGameEngine::engineReference;
namespace TenTrillion {

void TenTrillionGameEngine::Initialize() {
	// Initialize engine related stuff.
	engineReference = this;
	this->InitializeAllServices();
}

void TenTrillionGameEngine::InitializeAllServices() {
	SetEngineErrorHandler();

	this->renderingService = new TenRenderingService(this);
	this->renderingService->InitializeService();
}

void TenTrillionGameEngine::DeInitialize() {
	// De-Initialize the rendering service.
	this->renderingService->DeInitializeService();
	delete this->renderingService;
}
} // namespace TenTrillion
