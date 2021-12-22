#include "Resourse.h"
#include "Logger.h"
#include "Parser.h"
#include "Utils.h"

ItemBase::ItemBase(const std::string& name) :_name(name)
{}

bool Resourse::LoadResourses()
{
	auto configs = ParserManager->ParseSimple("main");
	for (const auto& config : configs)
	{
		ItemData* item = new ItemData(config);
		if (item->Load())
		{
			_data.insert(std::make_pair(config, item));
		}
		else
		{
			delete item;
			LoggerManager->logFull("Problem with loading " + config);
			return false;
		}
	}

	auto names = ParserManager->ParseSimple("resourses");

	for (const auto& name : names)
	{
		auto split = Utils::Split(name, ".");
		if (split.size() == 2) 
		{
			ItemBase* item = nullptr;
			if (split[1] == "png") {
				item = new ItemTexture(split[0]);
			}
			else if (split[1] == "ttf") 
			{
				item = new ItemFont(split[0]);
			}
			if (item->Load())
			{
				_data.insert(std::make_pair(split[0], item));
			}
			else
			{
				delete item;
				LoggerManager->logFull("Problem with loading " + name);

				return false;
			}
		}
	}
	
	
	return true;
}

void Resourse::Start()
{
	if (LoadResourses())
	{
		LoggerManager->logFull("All resourses succsefully loaded");
	}
}

void Resourse::Stop()
{
	for (auto& data : _data)
	{
		delete &data;
	}
	_data.clear();
}

ItemTexture::ItemTexture(const std::string& name) : ItemBase(name)
{}

bool ItemTexture::Load()
{
	if (!_t.loadFromFile("data/" + _name + ".png"))
	{
		LoggerManager->logFull("Problem with " + _name + ".png");
		return false;
	}
	_s.setTexture(_t);
	LoggerManager->logFull("Succsesfully loaded " + _name + ".png");
	return true;
}

ItemData::ItemData(const std::string& name) : ItemBase(name)
{
}

std::string ItemData::GetData(const std::string& data)
{
	const auto it = _data.find(data);
	if (it == _data.end())
	{
		LoggerManager->logFull("Problem with loading data " + data);
		return "";
	}
	return (*it).second;
}

bool ItemData::Load()
{
	_data = ParserManager->ParseDouble(_name);
	if (!_data.empty())
		return true;
	return false;
	
}

ItemFont::ItemFont(const std::string& name) : ItemBase(name)
{
}

sf::Font ItemFont::GetData()
{
	return _data;
}

bool ItemFont::Load()
{
	if (_data.loadFromFile("data/" + _name + ".ttf"))
	{
		LoggerManager->logFull("Font " + _name + " succsefully loaded");
		return true;
	}
	LoggerManager->logFull("Font " + _name + " not loaded");
	return false;
}
