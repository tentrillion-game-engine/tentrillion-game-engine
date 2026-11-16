#ifndef TENTRILLIONGAMEENGINE_TENVULKANERRORS_HPP
#define TENTRILLIONGAMEENGINE_TENVULKANERRORS_HPP

#include <exception>

class tentrillion_base_exception : std::exception {

  public:
	tentrillion_base_exception(const char *reason) { this->reason = reason; }
	const char *what() const noexcept override { return this->reason; }

  private:
	const char *reason{nullptr};
};

class tentrillion_reference_is_null : tentrillion_base_exception {
  public:
	tentrillion_reference_is_null(const char *reason)
		: tentrillion_base_exception(reason) {}
};

#ifdef __linux__
class tentrillion_no_xdg_session : tentrillion_base_exception {
  public:
	tentrillion_no_xdg_session(const char *reason)
		: tentrillion_base_exception(reason) {}
};
#endif

#endif