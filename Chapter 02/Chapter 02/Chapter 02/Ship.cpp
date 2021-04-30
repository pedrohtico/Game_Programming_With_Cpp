#include "Ship.h"
#include <vector>
#include "AnimationSpriteComponent.h"
#include <SDL.h>
#include "Game.h"

Ship::Ship(class Game* game)
	: Actor(game)
{
	this->velocity = { 0.f, 0.f };

	AnimationSpriteComponent* animComponent = new AnimationSpriteComponent(this);

	std::vector<SDL_Texture*> anim = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png")
	};
	
	animComponent->SetAnimationTextures(anim);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// update position
	Math::Vector2 pos = this->GetPosition();
	pos.x += this->velocity.x * deltaTime;
	pos.y += this->velocity.y * deltaTime;

	// restrict position to left side of screen
	if (pos.x < 25.0f)
		pos.x = 25.0f;
	else if (pos.x > 500.0f)
		pos.x = 500.0f;

	if (pos.y < 25.0f)
		pos.y = 25.0f;
	else if (pos.y > 695.0f)
		pos.y = 695.0f;

	this->SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state)
{
	this->velocity = { 0.f, 0.f };

	if (state[SDL_SCANCODE_W])
		this->velocity.y -= 300.f;

	if (state[SDL_SCANCODE_S])
		this->velocity.y += 300.f;

	if (state[SDL_SCANCODE_D])
		this->velocity.x += 250.f;

	if (state[SDL_SCANCODE_A])
		this->velocity.x -= 250.f;
}