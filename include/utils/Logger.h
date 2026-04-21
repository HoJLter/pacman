#pragma once
#include <string>
#include <memory>
#include <fstream>
#include "utils/Log.h"

class ILogger {
public:
	virtual ~ILogger() = default;
	virtual void log(LogLevel lvl, const std::string& msg) = 0;

protected:
	std::string getTimeString();
	std::string makeRecord(LogLevel lvl, const std::string& msg);
};

class FileLogger : public ILogger {
private:
	std::ofstream ofs;

public:
	FileLogger(std::string filename);
	FileLogger();

	void log(LogLevel lvl, const std::string& msg) override;
};

class ConsoleLogger : public ILogger {
public:
	void log(LogLevel lvl, const std::string& msg) override;
};