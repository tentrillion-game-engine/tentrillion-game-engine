#include "tentrillion_context.hpp"

#include <cstdint>

#include <tentrillion_constants.hpp>

tentrillion_context *
tentrillion_context::create_context(const char *application_title,
									const int32_t &window_width,
									const int32_t &window_height) {
	auto *tentrillion_window = new class tentrillion_context();

	tentrillion_window->window_width = window_width;
	tentrillion_window->window_height = window_height;

	return tentrillion_window;
}