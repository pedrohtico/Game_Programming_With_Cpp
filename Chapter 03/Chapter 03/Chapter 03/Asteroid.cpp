#include "Asteroid.h"

#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"

Asteroid::Asteroid(class Game* game)
	: Actor(game)
	, mCircle(nullptr)
{
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.f, 768.f));
	this->SetPosition(randPos);

	this->SetRotation(Random::GetFloatRange(0.f, static_cast<float>(Math::PI * 2)));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	this->GetGame()->RemoveAsteroid(this);
}
