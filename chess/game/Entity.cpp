#include "Entity.h"

void Entity::Draw()
{
	DrawSelf();
	for (const auto& child : _children)
	{
		child->Draw();
	}
}

void Entity::Update(const float dt)
{
	UpdateSelf(dt);
	for (const auto& child : _children)
	{
		child->Update(dt);
	}
}

bool Entity::OnEvent(sf::Event event)
{
	if (OnEventSelf(event));
	{
		return true;
	}
	for (const auto& child : _children)
	{
		if (child->OnEvent(event))
		{
			return true;
		}
	}
	return false;
}


Entity::Entity(const std::string& name) :_name(name), _isTopOwner(false), _parent(nullptr)
{
}

Entity::Entity(const std::string& name, sf::RenderWindow* window) : Entity(name)
{
	_window = window;
}

Entity::~Entity()
{
	for (auto& child : _children)
	{
		delete child;
	}
	_children.clear();
}

void Entity::AddChild(Entity* child)
{
	child->SetParent(this);
	_children.push_back(child);
}
