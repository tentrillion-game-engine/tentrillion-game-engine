

#ifndef TENTRILLIONGAMEENGINE_TENTRILLIONLOGGING_HPP
#define TENTRILLIONGAMEENGINE_TENTRILLIONLOGGING_HPP
#include <TenTrillionGameEngineExport.h>
#include <fstream>

namespace TenTrillion {
class TENTRILLIONGAMEENGINE_EXPORT LoggingSystem {
  public:
	enum LogLevel { INFO, WARNING, ERROR };

	LoggingSystem();

	void Log(LogLevel level, const char *message);

  private:
	std::ofstream logFile;

	/**
	 * This returns the specified LogLevel into a formatted string.
	 * @return A formatted logLevel name.
	 */
	static const char *returnLogName(LogLevel level);

	static void returnCurrentLogTime(const char *buffer);
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_TENTRILLIONLOGGING_HPP
