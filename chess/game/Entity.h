#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Event.h"


class Entity
{
	Entity* _parent;
	std::vector<Entity*> _children;
	bool _isTopOwner;
	std::string _name;
	sf::Vector2f _pos;
	

protected:
	sf::Sprite _sprite;
	sf::Vector2f _size;
	sf::RenderWindow* _window;
	void Draw();
	void Update(const float dt);
	bool OnEvent(sf::Event event);
private:
	virtual void DrawSelf() = 0;
	virtual void UpdateSelf(const float dt) = 0;
	virtual bool OnEventSelf(sf::Event event) = 0;

public:

	Entity(const std::string& name, sf::RenderWindow* window);
	virtual ~Entity();

	void SetTopOwner() { _isTopOwner = true; }
	bool IsTopOwner() { return _isTopOwner; }
	Entity* GetParent() { return _parent; }
	void SetParent(Entity* parent) { _parent = parent; }
	void AddChild(Entity* child);

	void SetWindow(sf::RenderWindow* window) { _window = window; }

	void SetName(const std::string& name) { _name = name; }
	std::string GetName() { return _name; }

	void SetPosition(const sf::Vector2f& pos) { _pos = pos; }
	sf::Vector2f GetPosition() { return _pos; }

	void SetSize(const sf::Vector2f& size) { _size = size; }
	sf::Vector2f GetSize() { return _size; }

	void ClearChildrenSafe();
	void ClearChidren();
};



