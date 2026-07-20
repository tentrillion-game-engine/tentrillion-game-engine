

#include "handlers/TenLoggingSystem.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

namespace TenTrillion {
TenLoggingSystem::TenLoggingSystem() {
	this->logFile = std::ofstream("current.log");

	if (!this->logFile) {
		std::cerr << "Failed to create logging subsystem! Stopping...";
		exit(1);
	}
}

const char *TenLoggingSystem::returnLogName(const LogLevel level) {
	switch (level) {
	case INFO:
		return "INFO";
	case WARNING:
		return "WARNING";
	case ERROR:
		return "ERROR";
	}
	return "UNIDENTIFIED";
}

void TenLoggingSystem::returnCurrentLogTime(const char *buffer) {
	char timeBuffer[100];

	const auto time = std::time(nullptr);
	const auto localTime = std::localtime(&time);

	std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S",
				  localTime);

	strncpy(timeBuffer, buffer, sizeof(timeBuffer));
}

void TenLoggingSystem::Log(const LogLevel level, const char *message) {
	char logBuffer[255];
	char timeBuffer[100];

	returnCurrentLogTime(timeBuffer);
	sprintf(logBuffer, "[%s/%s]: %s", timeBuffer, returnLogName(level),
			message);

	this->logFile << logBuffer << std::endl;
}

} // namespace TenTrillion
