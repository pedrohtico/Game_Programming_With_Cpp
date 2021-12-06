#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	: Component(owner, updateOrder)
	, mAngularSpeed(0.f)
	, mForwardSpeed(0.f)
{
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(this->mAngularSpeed))
	{
		float rot = this->owner->GetRotation();
		rot += this->mAngularSpeed * deltaTime;
		this->owner->SetRotation(rot);
	}

	if (!Math::NearZero(this->mForwardSpeed))
	{
		Vector2 pos = this->owner->GetPosition();
		pos += this->owner->GetForward() * this->mForwardSpeed * deltaTime;
		
		// (Screen wrapping code only for asteroids)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }
		
		this->owner->SetPosition(pos);
	}
}