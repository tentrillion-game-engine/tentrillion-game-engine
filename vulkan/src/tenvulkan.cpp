#include "tenvulkan.hpp"
#include <volk.h>

void tenvulkan::initialize_tenvulkan(const char *application_name) {
	if (volkInitialize() != VK_SUCCESS) {
	}
}