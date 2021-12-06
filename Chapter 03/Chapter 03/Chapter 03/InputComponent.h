#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <cstdint>
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	// getters and setters
	float GetMaxForwardSpeed() const { return this->maxForwardSpeed; }
	void SetMaxForwardSpeed(const float forward) { this->maxForwardSpeed = forward; }

	float GetMaxAngularSpeed() const { return this->maxAngularSpeed; }
	void SetMaxAngularSpeed(const float angular) { this->maxAngularSpeed = angular; }

	int GetForwardKey() const { return this->forwardKey; }
	void SetForwardKey(const int forward_key) { this->forwardKey = forward_key; }

	int GetBackwardKey() const { return this->backwardKey; }
	void SetBackwardKey(const int backward_key) { this->backwardKey = backward_key; }

	int GetClockwiseKey() const { return this->clockwiseKey; }
	void SetClockwiseKey(const int clockwise_key) { this->clockwiseKey = clockwise_key; }

	int GetCounterClockwiseKey() const { return this->counterClockwiseKey; }
	void SetCounterClockwiseKey(const int counter_clockwise_key) { this->counterClockwiseKey = counter_clockwise_key; }

private:
	float maxForwardSpeed, maxAngularSpeed;
	int forwardKey, backwardKey;
	int clockwiseKey, counterClockwiseKey;
};

#endif
