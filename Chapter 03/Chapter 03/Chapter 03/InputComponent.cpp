#include "InputComponent.h"

InputComponent::InputComponent(Actor* owner)
	: MoveComponent(owner)
	, forwardKey(0)
	, backwardKey(0)
	, clockwiseKey(0)
	, counterClockwiseKey(0)
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.f;

	if (keyState[forwardKey])
		forwardSpeed += this->maxForwardSpeed;

	if (keyState[backwardKey])
		forwardSpeed -= this->maxForwardSpeed;

	this->SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.f;

	if (keyState[clockwiseKey])
		angularSpeed += this->maxAngularSpeed;

	if (keyState[counterClockwiseKey])
		angularSpeed -= this->maxAngularSpeed;

	this->SetAngularSpeed(angularSpeed);
}
