#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H

#include "Component.h"
class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	// setters and getters
	float GetAngularSpeed() const { return this->mAngularSpeed; }
	float GetForwardSpeed() const { return this->mForwardSpeed; }
	void SetAngularSpeed(float a_speed) { this->mAngularSpeed = a_speed; }
	void SetForwardSpeed(float f_speed) { this->mForwardSpeed = f_speed; }

private:
	float mAngularSpeed, mForwardSpeed;
};

#endif // !MOVE_COMPONENT_H