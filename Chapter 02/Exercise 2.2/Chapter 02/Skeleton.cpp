#include "Skeleton.h"
#include "AnimationSpriteComponent.h"
#include <sstream>
#include "Game.h"

Skeleton::Skeleton(class Game* game)
	: Actor(game)
{
	this->velocity = { 0.f, 0.f };
	this->acc_y = 200.f;
	this->SetPosition({ 512.f, 720.f });

	AnimationSpriteComponent* anim = new AnimationSpriteComponent(this);
	std::vector<SDL_Texture*> anims;
	std::stringstream file;

	for (int i = 1; i < 19; ++i)
	{
		file << "Assets/Character";
		if (i < 10)
			file << '0';
		file << i << ".png";
		anims.emplace_back(game->GetTexture(file.str()));
		file.str("");
	}
	anim->SetAnimationTextures(anims);

	anim->AddAnimation("WALKING", std::make_pair(0, 5), true);
	anim->AddAnimation("JUMPING", std::make_pair(6, 14), false);
	anim->AddAnimation("PUNCHING", std::make_pair(15, 17), false);
	anim->SetCurrentAnimation("WALKING");
	anim->SetAnimationFPS(24.f);
	this->anim = anim;
}

void Skeleton::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	if (this->anim->GetCurrentAnimation() == "JUMPING")
	{
		this->velocity.y += this->acc_y * deltaTime;
	}

	// update position
	Math::Vector2 pos = this->GetPosition();
	pos.x += this->velocity.x * deltaTime;
	pos.y += this->velocity.y * deltaTime;

	// restrict position to screen
	// img size is 128x128 px and screen size is 1024x720 px
	if (pos.x < 50.f)
		pos.x = 50.f;
	else if (pos.x > 1034.f)
		pos.x = 1034.f;

	if (pos.y > 656.f)
	{
		if (this->anim->GetCurrentAnimation() == "JUMPING")
		{
			this->anim->SetCurrentAnimation(0);
			this->anim->SetAnimationFPS(24.f);
		}
		pos.y = 656.f;
	}

	this->SetPosition(pos);
}

void Skeleton::ProcessKeyboard(const uint8_t* state)
{
	if (this->anim->GetCurrentAnimation() != "JUMPING")
		this->velocity.y = 0.f;
	this->velocity.x = 0.f;

	if (state[SDL_SCANCODE_RIGHT])
		this->velocity.x += 250.f;

	if (state[SDL_SCANCODE_LEFT])
		this->velocity.x -= 250.f;

	if (state[SDL_SCANCODE_UP] && this->anim->GetCurrentAnimation() != "JUMPING")
	{
		this->velocity.y = -100.f;
		this->anim->SetCurrentAnimation("JUMPING");
		this->anim->SetAnimationFPS(9.f);
	}

	if (state[SDL_SCANCODE_SPACE] && this->anim->GetCurrentAnimation() != "PUNCHING"
		&& this->anim->GetCurrentAnimation() != "JUMPING")
	{
		this->anim->SetCurrentAnimation("PUNCHING");
	}
}