#pragma once

#include <unordered_map>
#include <algorithm>
#include "Singleton.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class ItemBase
{
protected:
	std::string _name;

public:
	ItemBase(const std::string& name);
	virtual bool Load() = 0;
};

class ItemTexture : public ItemBase
{
	sf::Texture _t;
	sf::Sprite _s;
	
public:
	ItemTexture(const std::string& name);
	sf::Sprite GetSprite() { return _s; }
	virtual bool Load() override;
};

class ItemData : public ItemBase
{
	std::unordered_map<std::string, std::string> _data;
public:
	ItemData(const std::string& name);
	std::string GetData(const std::string& data);
	virtual bool Load() override;
};

class ItemFont : public ItemBase
{
	sf::Font _data;
public:
	ItemFont(const std::string& name);
	sf::Font GetData();
	virtual bool Load() override;
};

class Resourse
{
	std::unordered_map<std::string, std::shared_ptr<ItemBase>> _data;
	bool LoadResourses();

public:
	
	void Start();
	void Stop();
	template <typename T>
	std::shared_ptr<T> GetData(const std::string& hash) 
	{
		const auto it = _data.find(hash);
		if (it == _data.end())
		{
			return nullptr;
		}
		return std::static_pointer_cast<T>((*it).second);
	}
};

typedef Singletons<Resourse> ResourseSingleton;
#define ResourseManager (ResourseSingleton::ref())
