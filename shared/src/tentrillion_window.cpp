#include "tentrillion_window.hpp"

#include <cstdint>

#include <tentrillion_constants.hpp>

tentrillion_window *
tentrillion_window::create_context(const char *application_title,
								   const int32_t &window_width,
								   const int32_t &window_height) {
	auto *tentrillion_window = new class tentrillion_window();

	tentrillion_window->window_width = window_width;
	tentrillion_window->window_height = window_height;

#ifdef TENTRILLIONGAMEENGINE_TENVULKAN_HPP
// TODO
#endif

	return tentrillion_window;
}
