#pragma once
#include <string>
#include <memory>

class ILogger;

enum class LogLevel {
	Debug,
	Info,
	Warn,
	Error
};

enum class LoggerType {
	Console,
	File
};

class Log {
private:
	static std::unique_ptr<ILogger> curLogger;
	static std::string filename;

public:
	static void setLogger(LoggerType type);
	static void setFilename(const std::string& filename);

	static void debug(const std::string& msg);
	static void info(const std::string& msg);
	static void warn(const std::string& msg);
	static void error(const std::string& msg);
};
