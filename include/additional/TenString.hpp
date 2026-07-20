

#ifndef TENTRILLIONGAMEENGINE_TENSTRING_HPP
#define TENTRILLIONGAMEENGINE_TENSTRING_HPP
#include "handlers/TenLoggingSystem.hpp"

#include <TenTrillionGameEngineExport.h>
#include <string>

namespace TenTrillion {

/**
 * TenString is the string wrapper for cross-platform useability.
 * Due to Windows requiring wstring, this wrapper was created for easier use
 * with the TenTrillion.
 */
class TENTRILLIONGAMEENGINE_EXPORT TenString {
  public:
	~TenString();
	/**
	 * The string wrapper for int.
	 * @param data The int data.
	 */
	explicit TenString(int data);
	/**
	 * The string wrapper for long.
	 * @param data The long data.
	 */
	explicit TenString(long data);
	/**
	 * The string wrapper for unsigned longs.
	 * @param data The unsigned long data.
	 */
	explicit TenString(unsigned long data);
	/**
	 * The string wrapper for doubles.
	 * @param data The double data.
	 */
	explicit TenString(double data);
	/**
	 * The string wrapper for const char's.
	 * @param data The const char* data.
	 */
	explicit TenString(const char *data);
	/**
	 * The string wrapper for std::string.
	 * @param data The std::string data.
	 */
	explicit TenString(std::string &data);

#ifdef __linux__
	/**
	 * Return the std::string associated with this TenString.
	 * @return The speficified string.
	 */
	std::string getString();
#endif

	[[nodiscard]] const char *getCString() const;

#ifdef WIN32
	/**
	 * The string wrapper for widestrings, Windows only.
	 * @param data The std::wstring data.
	 */
	explicit TenString(std::wstring &data);

	/**
	 * Get the widestring associated with this TenString.
	 * @return The specified widestring.
	 */
	std::wstring getString();
#endif

  private:
#ifdef __linux__
	char *data;
#endif

#ifdef WIN32
	wchar_t *data;
#endif
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_TENSTRING_HPP
