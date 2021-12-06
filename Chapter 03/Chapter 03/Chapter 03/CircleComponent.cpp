#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	: Component(owner)
	, radius(0.f)
{
}

float CircleComponent::GetRadius() const
{
	return this->radius;
}

const Vector2& CircleComponent::GetCenter() const
{
	return this->owner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// create a vector between the centers and get its magnitude squared
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSquared = static_cast<float>(pow(diff.Mag(), 2));

	// get the square of radius sum
	float sum = a.GetRadius() + b.GetRadius();
	float radiusSquared = sum * sum;

	// checks intersection
	return distSquared <= radiusSquared;
}
