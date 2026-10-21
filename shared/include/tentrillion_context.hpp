#ifndef TENTRILLIONGAMEENGINE_TENTRILLION_CONTEXT_HPP
#define TENTRILLIONGAMEENGINE_TENTRILLION_CONTEXT_HPP
#include <cstdint>
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

class tentrillion_context {
  public:
	static tentrillion_context *create_context(const char *application_title,
											   const int32_t &window_width,
											   const int32_t &window_height);

  private:
	int32_t window_width;
	int32_t window_height;
};

#endif // TENTRILLIONGAMEENGINE_TENTRILLION_CONTEXT_HPP
