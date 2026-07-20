

#ifndef TENTRILLIONGAMEENGINE_TENTRILLIONLOGGING_HPP
#define TENTRILLIONGAMEENGINE_TENTRILLIONLOGGING_HPP
#include <TenTrillionGameEngineExport.h>
#include <fstream>

namespace TenTrillion {
class TENTRILLIONGAMEENGINE_EXPORT TenLoggingSystem {
  public:
	enum LogLevel { INFO, WARNING, ERROR };

	TenLoggingSystem();

	void Log(LogLevel level, const char *message);

	/**
	 * Get the current logging system instance.
	 * @return The current pointer to the logger.
	 */
	static TenLoggingSystem *GetTenLoggingSystem();

  private:
	/**
	 * The current logging system instance.
	 */
	static TenLoggingSystem *TenLoggingSystemInstance;

	/**
	 * The current log file.
	 */
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
