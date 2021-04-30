#include "AnimationSpriteComponent.h"
#include "Actor.h"

AnimationSpriteComponent::AnimationSpriteComponent(class Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
{
	this->currentFrame = 0.f;
	this->animationFPS = 24.f;
	this->currentAnimation = nullptr;
}

AnimationSpriteComponent::~AnimationSpriteComponent()
{
	for (auto a : this->animations)
		delete a;
}

void AnimationSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (this->currentAnimation)
	{
		this->currentFrame += this->animationFPS * deltaTime; // updates current animation frame

		int h = this->currentAnimation->range.second;
		int l = this->currentAnimation->range.first;
		bool wrap = this->currentAnimation->wrap;

		while (this->currentFrame >= h + 1) // checks if wrap is needed
		{
			if (wrap)
				this->currentFrame -= h - l + 1; // wraps
			else
			{
				this->SetCurrentAnimation(0); // sets the animation to first animation
				break;
			}
		}

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

void AnimationSpriteComponent::AddAnimation(const std::string& name, const std::pair<int, int>& range,
											bool wrap)
{
	Animation* anim = new Animation();
	anim->animationName = name;
	anim->range = range;
	anim->wrap = wrap;
	this->animations.emplace_back(anim);
	if (this->animations.size() == 1)
		this->currentAnimation = anim;
}

void AnimationSpriteComponent::SetCurrentAnimation(const std::string &anim_name)
{
	for (auto a : this->animations)
	{
		if (a->animationName == anim_name)
		{
			this->currentAnimation = a;
			this->currentFrame = static_cast<float>(a->range.first);
			return;
		}
	}
}

void AnimationSpriteComponent::SetCurrentAnimation(int index)
{
	if (index >= 0 && index < (int) this->animations.size())
	{
		this->currentAnimation = this->animations[index];
		this->currentFrame = static_cast<float>(this->animations[index]->range.first);
	}
	else
	{
		this->currentFrame = static_cast<float>(this->currentAnimation->range.first);
	}
}