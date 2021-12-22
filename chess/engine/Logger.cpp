#include "Logger.h"
#include <iostream>
#include <ctime>



Logger::Logger() : outFile("log.txt")
{
	_start = std::chrono::system_clock::now();
	logFull("Logger started\n");
}

Logger::~Logger()
{
	outFile.close();
}

void Logger::logFull(const std::string& message)
{
	logScreen(message);
	logFile(message);
}

void Logger::logScreen(const std::string& message)
{
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - _start;
	std::cout << elapsed_seconds.count() << " : " << message << "\n";
}

void Logger::logFile(const std::string& message)
{
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - _start;
	outFile << elapsed_seconds.count() << " : " << message << "\n";
}
