#include "Parser.h"

#include <sstream>
#include "Logger.h"

std::vector<std::string> Parser::ParseSimple(const std::string& cfg)
{

	std::vector<std::string> res;
	std::ifstream config("data/configs/" + cfg + ".cfg");
	std::string line;
	if (config.is_open()) 
	{
		while (std::getline(config, line))
		{
			res.push_back(line);
		}
		config.close();
	}
	LogEmpty(res.empty(), cfg);

	return res;
}

std::unordered_map<std::string, std::string> Parser::ParseDouble(const std::string& cfg)
{
	std::unordered_map<std::string, std::string> res;
	std::string line, var1, var2;

	std::ifstream config("data/configs/" + cfg + ".cfg");
	if (config.is_open())
	{
		while (std::getline(config, line))
		{
			std::istringstream iss(line);
			if (!(iss >> var1 >> var2)) { break; } // end
			res[var1] = var2;
		}
		config.close();
	}
	LogEmpty(res.empty(), cfg);
	return res;
}


void Parser::LogEmpty(const bool isEmpty, const std::string& cfg)
{
	if (!isEmpty)
	{
		LoggerManager->logFull("Succsesfully readed " + cfg + ".cfg");
	}
	else
	{
		LoggerManager->logFull("Problem with reading " + cfg + ".cfg");
	}
}
