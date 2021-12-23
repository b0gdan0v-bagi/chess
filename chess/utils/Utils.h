#pragma once
#include <string>
#include <vector>


enum class eCellStyle
{
	Black,
	White
};

enum class eDirection
{
	Top,
	Right,
	Bottom,
	Left,
	Count
};

enum class ePlayerColor
{
	Black,
	White,
	Count
};

enum class eFigureType
{
	Pawn,
	Count
};

namespace Utils
{
	static std::vector<std::string> Split(const std::string& str, const std::string& delimiter)
	{
		std::string s = str;
		std::vector<std::string> res;

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			res.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		res.push_back(s);
		return res;
	}
}