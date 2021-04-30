#include "AnimationSpriteComponent.h"
#include "Actor.h"

AnimationSpriteComponent::AnimationSpriteComponent(class Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
{
	this->currentFrame = 0.f;
	this->animationFPS = 24.f;
}

void AnimationSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (this->textures.size() > 0)
	{
		this->currentFrame += this->animationFPS * deltaTime; // updates current animation frame

		while (this->currentFrame >= this->textures.size()) // checks if wrap is needed
			this->currentFrame -= this->textures.size(); // wraps

		this->SetTexture(this->textures[static_cast<int>(this->currentFrame)]); // set current texture
	}
}

void AnimationSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture*>& textures)
{
	this->textures = textures;
	if (this->textures.size() > 0)
	{
		this->currentFrame = 0.f;
		this->SetTexture(this->textures[0]);
	}
}