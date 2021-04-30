#include "Actor.h"
#include <algorithm>
#include "Component.h"
#include "Game.h"


Actor::Actor(class Game* game)
{
	this->game = game;
	this->state = State::EActive;
	this->position = {
		0.f, 0.f
	};
	this->rotation = 0.f;
	this->scale = 1.f;

	this->game->AddActor(this);
}

Actor::~Actor()
{
	this->game->RemoveActor(this);
	while (!this->components.empty())
		delete this->components.back();
}

void Actor::Update(float deltaTime)
{
	if (this->state == Actor::State::EActive)
	{
		this->UpdateComponents(deltaTime);
		this->UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto c : this->components)
		c->Update(deltaTime);
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(class Component* component)
{
	auto iter = this->components.begin();
	for (; iter != this->components.end(); ++iter)
	{
		if (component->GetUpdateOrder() < (*iter)->GetUpdateOrder())
			break;
	}
	this->components.insert(iter, component);
}

void Actor::RemoveComponent(class Component* component)
{
	auto iter = std::find(this->components.begin(), this->components.end(), component);
	if (iter != this->components.end())
		this->components.erase(iter);
}
