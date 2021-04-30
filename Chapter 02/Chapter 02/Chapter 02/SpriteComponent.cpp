#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder)
	: Component (owner)
{
	this->texture = nullptr;
	this->drawOrder = drawOrder;
	this->textureWidth = 0;
	this->textureHeight = 0;
	
	this->owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	this->owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	this->texture = texture;

	SDL_QueryTexture(texture, nullptr, nullptr, &this->textureWidth, &this->textureHeight);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (this->texture)
	{
		SDL_Rect r = { 0, 0, 0, 0 };
		r.w = static_cast<int>(this->textureWidth * this->owner->GetScale()); // SPRITE WIDTH
		r.h = static_cast<int>(this->textureHeight * this->owner->GetScale()); // SPRITE HEIGHT

		r.x = static_cast<int>(this->owner->GetPosition().x - r.w / 2.f ); // SPRITE X POS
		r.y = static_cast<int>(this->owner->GetPosition().y - r.h / 2.f ); // SPRITE Y POS

		// draw texture rect
		SDL_RenderCopyEx(
			renderer,
			this->texture,
			nullptr,
			&r,
			Math::RadiansToDegree(this->owner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}
