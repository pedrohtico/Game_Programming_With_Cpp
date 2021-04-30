#ifndef SKELETON_H
#define SKELETON_H

#include "Actor.h"
#include "Math.h"

class Skeleton : public Actor
{
public:
	Skeleton(class Game* game);

	void UpdateActor(float deltaTime) override;

	void ProcessKeyboard(const uint8_t* state);

	float GetXVelocity() const { return this->velocity.x; }
	float GetYVelocity() const { return this->velocity.y; }
private:
	Math::Vector2 velocity;
	float acc_y;
	class AnimationSpriteComponent* anim;
};

#endif // SKELETON_H