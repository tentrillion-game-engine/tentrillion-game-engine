#include "additional/TenString.hpp"

#include "TenTrillionGameEngine.hpp"

#include <charconv>
#include <cstring>

namespace TenTrillion {
TenString::~TenString() {
	// Free the memory containing the string data.
	free(this->data);
}

TenString::TenString(const char *data) { this->data = strdup(data); }

TenString::TenString(std::string &data) { this->data = data.data(); }

#ifdef WIN32
TenString::TenString(std::wstring &data) {
	// The TenString doesn't have support for widestrings on Linux, as Linux
	// already initializes it's strings as UTF-8.
	this->data = data.data();
}

std::wstring TenString::getString() { return {this->data}; }
#endif

#ifdef __linux__
template <typename T>
static char *
#endif

#ifdef WIN32
	template <typename T>
	static wchar_t *
#endif

	/**
	 * This automatically converts the specified data to a string.
	 * @tparam T The type that will be
	 * @param data The specified data.
	 * @return The buffer that is created.
	 */
	getConversionString(T data) {
#ifdef __linux__
	const auto buffer = new char[sizeof(data)];
	if (auto [ptr, ec] =
			std::to_chars(buffer, buffer + sizeof(buffer) - 1, data);
		ec == std::errc()) {
		*ptr = '\0';
		return buffer;
	}
	return nullptr;
#endif

#ifdef WIN32
	// TODO: Implement Windows Support!
#endif
}

TenString::TenString(const double data) {
	this->data = getConversionString(data);
}

std::string TenString::getString() { return {this->data}; }

TenString::TenString(const int data) { this->data = getConversionString(data); }

TenString::TenString(const long data) {
	this->data = getConversionString(data);
}

TenString::TenString(const unsigned long data) {
	this->data = getConversionString(data);
}

const char *TenString::getCString() const { return this->data; }

} // namespace TenTrillion