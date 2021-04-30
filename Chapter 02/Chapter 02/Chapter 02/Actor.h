#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include "Math.h"

class Actor
{
public:
	enum class State {
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	// getters and setters
	State GetState() const { return this->state; }
	class Game* GetGame() const { return this->game; }

	float GetScale() const { return this->scale; }
	void SetScale(float scale) { this->scale = scale; }

	const Math::Vector2& GetPosition() const { return this->position; }
	void SetPosition(const Math::Vector2& position) { this->position = position; }

	float GetRotation() const { return this->rotation; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State state;

	// transform
	Math::Vector2 position;
	float rotation; // RADIANS
	float scale; // 1.f for 100% scale

	// components held
	std::vector<class Component*> components;
	class Game* game;

};

#endif // !ACTOR_H