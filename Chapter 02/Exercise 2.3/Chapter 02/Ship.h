#ifndef SHIP_H
#define SHIP_H

#include "Actor.h"
#include "Math.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;

	void ProcessKeyboard(const uint8_t* state);

	float GetXVelocity() const { return this->velocity.x; }
	float GetYVelocity() const { return this->velocity.y; }
private:
	Math::Vector2 velocity;
};

#endif // !SHIP_H