#pragma once
#include "Singleton.h"
#include <fstream>
#include <chrono>

class Logger
{
	std::ofstream outFile;
	std::chrono::system_clock::time_point _start;

public:
	Logger();
	~Logger();
	void logFull(const std::string& message);
	void logScreen(const std::string& message);
	void logFile(const std::string& message);
};

typedef Singletons<Logger> LoggerSingleton;
#define LoggerManager (LoggerSingleton::ref())


