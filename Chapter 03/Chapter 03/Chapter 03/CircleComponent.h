#ifndef CIRCLE_COMPONENT_H
#define CIRCLE_COMPONENT_H

#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner);

	void SetRadius(float radius) { this->radius = radius; }
	float GetRadius() const;

	const Vector2& GetCenter() const;
private:
	float radius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);

#endif // !CIRCLE_COMPONENT_H