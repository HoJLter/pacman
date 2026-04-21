#include "utils/Logger.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>



// INTERFACE
std::string ILogger::getTimeString() {
	time_t timestamp = time(nullptr);
	tm curTime = *localtime(&timestamp);

	std::ostringstream stream;
	stream << std::setfill('0')
		<< std::setw(2) << curTime.tm_mday << "."
		<< std::setw(2) << (curTime.tm_mon + 1) << "."
		<< std::setw(4) << (curTime.tm_year + 1900) << " "
		<< std::setw(2) << curTime.tm_hour << ":"
		<< std::setw(2) << curTime.tm_min << ":"
		<< std::setw(2) << curTime.tm_sec
		<< std::setfill(' ');

	return stream.str();
}

std::string ILogger::makeRecord(LogLevel lvl, const std::string& msg) {
	std::ostringstream stream;
	std::string levelStr;

	switch (lvl) {
	case LogLevel::Debug: levelStr = "[DEBUG]"; break;
	case LogLevel::Info:  levelStr = "[INFO]";  break;
	case LogLevel::Warn:  levelStr = "[WARN]";  break;
	case LogLevel::Error: levelStr = "[ERROR]"; break;
	}

	stream << std::left << std::setw(7) << levelStr
		<< " | " << getTimeString()
		<< " | " << msg << std::endl;

	return stream.str();
}


// CONSOLE LOGGER
void ConsoleLogger::log(LogLevel lvl, const std::string& msg) {
	std::cout << makeRecord(lvl, msg);
}


// FILE LOGGER
FileLogger::FileLogger(std::string filename) : ofs(filename) {
	if (!ofs.is_open()) {
		throw std::runtime_error("[ERROR] Log file create error");
	}
}

FileLogger::FileLogger(): ofs("app.log") {
	if (!ofs.is_open()) {
		throw std::runtime_error("[ERROR] Log file create error");
	}
}

void FileLogger::log(LogLevel lvl, const std::string& msg) {
	ofs << makeRecord(lvl, msg);
}
