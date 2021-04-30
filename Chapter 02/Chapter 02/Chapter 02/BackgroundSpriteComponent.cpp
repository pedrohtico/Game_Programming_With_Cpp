#include "BackgroundSpriteComponent.h"
#include "Actor.h"

BackgroundSpriteComponent::BackgroundSpriteComponent(class Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
{
	this->screenSize = { 0, 0 };
	this->scrollSpeed = 0.f;
}

void BackgroundSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	for (auto &t : this->bgTextures)
	{
		t.offset.x += this->scrollSpeed * deltaTime;

		if (t.offset.x < -1 * this->screenSize.x)
			t.offset.x = (this->bgTextures.size() - 1) * this->screenSize.x - 1;
	}
}

void BackgroundSpriteComponent::Draw(SDL_Renderer* renderer)
{
	SDL_Rect r = { 0, 0, 0, 0 };;
	for (auto &t : this->bgTextures)
	{
		r.w = static_cast<int>(this->screenSize.x);
		r.h = static_cast<int>(this->screenSize.y);

		r.x = static_cast<int>(this->owner->GetPosition().x - r.w / 2.f + t.offset.x);
		r.y = static_cast<int>(this->owner->GetPosition().y - r.h / 2.f + t.offset.y);

		SDL_RenderCopy(renderer, t.bgTexture, nullptr, &r);
	}

}

void BackgroundSpriteComponent::SetBackgroundTextures(const std::vector<SDL_Texture*>& bg_textures)
{
	int count = 0;
	for (auto t : bg_textures)
	{
		BGTexture temp = { nullptr, {0, 0} };
		temp.bgTexture = t;
		temp.offset = { count * this->screenSize.x, 0 };
		this->bgTextures.emplace_back(temp);
		++count;
	}
}