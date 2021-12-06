#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Laser::Laser(Game* game)
	: Actor(game)
	, mCircle(nullptr)
	, deathTimer(1.f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.f);
}

void Laser::UpdateActor(float deltaTime)
{
	// If we run out of time, laser is dead
	deathTimer -= deltaTime;
	if (deathTimer <= 0.0f)
	{
		this->SetState(Actor::State::EDead);
	}
	else
	{
		// Do we intersect with an asteroid?
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				// The first asteroid we intersect with,
				// set ourselves and the asteroid to dead
				SetState(Actor::State::EDead);
				ast->SetState(Actor::State::EDead);
				break;
			}
		}
	}
}