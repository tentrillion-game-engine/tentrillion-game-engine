#ifndef TENTRILLIONGAMEENGINE_TENVULKANERRORS_HPP
#define TENTRILLIONGAMEENGINE_TENVULKANERRORS_HPP

#include <exception>
class tentrillion_reference_is_null : std::exception {

  public:
	tentrillion_reference_is_null(const char *reason) { this->reason = reason; }
	const char *what() const noexcept override { return this->reason; }

  private:
	const char *reason{nullptr};
};

#endif