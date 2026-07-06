#include "Main.hpp"

#include <rendering/RenderingService.hpp>

#include <volk.h>

TenTrillion::Main *TenTrillion::Main::engineReference;
namespace TenTrillion {
void Main::Initialize() {
	// Initialize engine related stuff.
	engineReference = this;
	this->InitializeAllServices();
}

void Main::InitializeAllServices() {
	this->renderingService =
		std::unique_ptr<RenderingService>(new RenderingService(this));
	this->renderingService->InitializeService();
}

void Main::DeInitialize() {}
} // namespace TenTrillion
