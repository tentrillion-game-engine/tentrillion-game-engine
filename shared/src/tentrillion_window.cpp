#include "tentrillion_window.hpp"
#include "GLFW/glfw3.h"

#include <cstdint>

#include <tentrillion_constants.hpp>

tentrillion_window::tentrillion_window(const char *application_title,
									   const int32_t &window_width,
									   const int32_t &window_height) {

	this->window_width = window_width;
	this->window_height = window_height;

	if (!glfwInit()) {
		// TODO
	}
#ifdef TENTRILLION_VULKAN
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

#ifdef TENTRILLION_OPENGL

#endif
}
