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

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState) {}

	// getters and setters
	class Game* GetGame() const { return this->game; }

	float GetScale() const { return this->scale; }
	void SetScale(float scale) { this->scale = scale; }

	const Vector2& GetPosition() const { return this->position; }
	void SetPosition(const Vector2& position) { this->position = position; }

	float GetRotation() const { return this->rotation; }
	void SetRotation(const float rotation) { this->rotation = rotation; }

	Vector2 GetForward() const { return Vector2(Math::Cos(this->rotation), -Math::Sin(this->rotation)); }

	State GetState() const { return this->state; }
	void SetState(State state) { this->state = state; }

	// component handlers
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State state;

	// transform
	Vector2 position;
	float rotation; // RADIANS
	float scale; // 1.f for 100% scale

	// components held
	std::vector<class Component*> components;
	class Game* game;

};

#endif // !ACTOR_H