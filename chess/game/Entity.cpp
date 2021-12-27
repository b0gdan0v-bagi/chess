#include "Entity.h"
#include "Logger.h"

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

bool Entity::OnEvent(GameEventBase* event)
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

Entity::Entity(const std::string& name) 
	:_name(name)
	,_isTopOwner(false)
	,_parent(nullptr)
{}

Entity::~Entity()
{
	ClearChildrenSafe();
}

void Entity::AddChild(Entity* child)
{
	child->SetParent(this);
	_children.push_back(child);
}

void Entity::ClearChildrenSafe()
{
	for (auto& child : _children)
	{
		//LoggerManager->logFull(child->GetName() + " succsefully deleted");
		delete child;
	}
	_children.clear();
}

void Entity::ClearChidren()
{
	_children.clear();
}
