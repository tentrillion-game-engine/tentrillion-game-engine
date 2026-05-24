#include "renderingService.hpp"

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_video.h"
#include "SDL3/SDL_vulkan.h"
#include "tentrillion.hpp"
#include "tentrillionService.hpp"
#ifdef TENTRILLION_BACKEND_VULKAN
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#endif

namespace TenTrillionGameEngine {
RenderingService::RenderingService(const Vector windowSize,
								   const char *windowTitle,
								   TentrillionEngine *engine)
	: TenTrillionService("WindowService", engine) {
	this->windowSize = windowSize;

#ifdef TENTRILLION_BACKEND_VULKAN
	backend = SDL_Vulkan_LoadLibrary(NULL) ? RenderingBackend::VULKAN
										   : RenderingBackend::OPENGL;
#else
	backend = RenderingBackend::OPENGL;
#endif

	this->windowInstance = SDL_CreateWindow(
		windowTitle, this->windowSize.x, this->windowSize.z,
		backend == VULKAN ? SDL_WINDOW_VULKAN : SDL_WINDOW_OPENGL);

#ifdef TENTRILLION_BACKEND_VULKAN
	this->createVkInstance();

	if (!SDL_Vulkan_CreateSurface(this->windowInstance, this->vkInstance,
								  nullptr, &this->vkSurfaceKhr)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Failed to create Vulkan surface");
		exit(1);
	}

	this->createVkDevice();
#else

#endif
}

Vector &RenderingService::getWindowSize() { return this->windowSize; }

SDL_Renderer *RenderingService::getRendererInstance() const {
	return rendererInstance;
}

void RenderingService::setRendererInstance(SDL_Renderer *m_rendererInstance) {
	this->rendererInstance = m_rendererInstance;
}

SDL_Window *RenderingService::getWindowInstance() const {
	return this->windowInstance;
}

void RenderingService::quitService() { SDL_Quit(); }
} // namespace TenTrillionGameEngine

#ifdef TENTRILLION_BACKEND_VULKAN

void TenTrillionGameEngine::RenderingService::createVkInstance() {
	const char *const *vkInstanceExtensions =
		SDL_Vulkan_GetInstanceExtensions(&this->vkInstanceExtensionsCount);

	if (vkInstanceExtensions == nullptr) {
		SDL_LogWarn(
			SDL_LOG_CATEGORY_APPLICATION,
			"Attempted to recieve Instance Extensions, ENDED IN FAILURE!");
		exit(1);
	}

	VkInstanceCreateInfo vkInstanceCreateInfo = {};
	vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vkInstanceCreateInfo.enabledExtensionCount =
		this->vkInstanceExtensionsCount;
	vkInstanceCreateInfo.ppEnabledExtensionNames = vkInstanceExtensions;
	if (vkCreateInstance(&vkInstanceCreateInfo, nullptr, &this->vkInstance) !=
		VK_SUCCESS) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Failed to create Vulkan instance\n");
		exit(1);
	}

	uint32_t physicalDeviceCount = 0;
	vkEnumeratePhysicalDevices(this->vkInstance, &physicalDeviceCount, nullptr);
	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	vkEnumeratePhysicalDevices(this->vkInstance, &physicalDeviceCount,
							   physicalDevices.data());

	this->vkPhysicalDevice = physicalDevices[0];
}

void TenTrillionGameEngine::RenderingService::createVkDevice() {
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(this->vkPhysicalDevice,
											 &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(
		this->vkPhysicalDevice, &queueFamilyCount, queueFamilies.data());

	uint32_t graphicsQueueFamilyIndex{UINT32_MAX};
	uint32_t presentQueueFamilyIndex{UINT32_MAX};
	VkBool32 supportsGraphicsQueue{false};
	uint32_t i{0};

	for (const VkQueueFamilyProperties queueFamily : queueFamilies) {
		if (graphicsQueueFamilyIndex == UINT32_MAX &&
			queueFamily.queueCount > 0 &&
			queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			graphicsQueueFamilyIndex = i;

		if (presentQueueFamilyIndex == UINT32_MAX)
			vkGetPhysicalDeviceSurfaceSupportKHR(this->vkPhysicalDevice, i,
												 this->vkSurfaceKhr,
												 &supportsGraphicsQueue);
		if (supportsGraphicsQueue)
			presentQueueFamilyIndex = i;
		++i;
	}

	float queuePriority{1.0f};

	VkDeviceQueueCreateInfo vkDeviceQueueCreateInfo = {
		VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		nullptr,
		0,
		graphicsQueueFamilyIndex,
		1,
		&queuePriority};

	VkPhysicalDeviceFeatures deviceFeatures = {};
	const char *deviceExtensionNames[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	const VkDeviceCreateInfo deviceCreateInfo = {
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		nullptr,
		0,
		1,
		&vkDeviceQueueCreateInfo,
		0,
		nullptr,
		1,
		deviceExtensionNames,
		&deviceFeatures};

	vkCreateDevice(this->vkPhysicalDevice, &deviceCreateInfo, nullptr,
				   &this->vkDevice);
}
#endif