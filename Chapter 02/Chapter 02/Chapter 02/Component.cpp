#include "Component.h"

#include "Actor.h"

Component::Component(class Actor* owner, int updateorder)
{
	this->owner = owner;
	this->updateOrder = updateorder;

	this->owner->AddComponent(this);
}

Component::~Component()
{
	this->owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}