#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>


class Parser
{
	void LogEmpty(const bool isEmpty, const std::string& cfg);
public:
	std::vector<std::string> ParseSimple(const std::string& cfg);
	std::unordered_map<std::string, std::string> ParseDouble(const std::string& cfg);
};

typedef Singletons<Parser> ParserSingleton;
#define ParserManager (ParserSingleton::ref())


