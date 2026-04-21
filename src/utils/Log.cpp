#include "utils/Logger.h"

// [DEBUG] | 12.04.2026 12:32:50 | Button created
std::unique_ptr<ILogger> Log::curLogger = nullptr;
std::string Log::filename = "app.log";

// STATIC WRAPPER
void Log::setLogger(LoggerType type) {
	switch (type) {
	case LoggerType::Console: {
		curLogger = std::make_unique<ConsoleLogger>();
		break;
	}
	case LoggerType::File: {
		curLogger = std::make_unique<FileLogger>();
		break;
	default:
		curLogger = std::make_unique<ConsoleLogger>();
		break;
	}
	}
}

void Log::setFilename(const std::string& fname) {
	filename = fname;
}

void Log::debug(const std::string& msg) {
	curLogger->log(LogLevel::Debug, msg);
}

void Log::info(const std::string& msg) {
	curLogger->log(LogLevel::Info, msg);
}

void Log::warn(const std::string& msg) {
	curLogger->log(LogLevel::Warn, msg);
}

void Log::error(const std::string& msg) {
	curLogger->log(LogLevel::Error, msg);
}
