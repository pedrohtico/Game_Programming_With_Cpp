#ifndef BACKGROUND_SPRITE_COMPONENT_H
#define BACKGROUND_SPRITE_COMPONENT_H

#include "SpriteComponent.h"
#include <SDL.h>
#include <vector>
#include "Math.h"

class BackgroundSpriteComponent : public SpriteComponent
{
public:
	BackgroundSpriteComponent(class Actor* owner, int drawOrder = 10);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	void SetBackgroundTextures(const std::vector<SDL_Texture*> &bg_textures);

	// getters and setters
	float GetScrollSpeed() const { return this->scrollSpeed; }
	void SetScrollSpeed(const float scroll_speed) { this->scrollSpeed = scroll_speed; }
	void SetScreenSize(const Math::Vector2& screen_size) { this->screenSize = screen_size; }
private:
	struct BGTexture {
		SDL_Texture* bgTexture;
		Math::Vector2 offset;
	};
	std::vector<BGTexture> bgTextures;

	Math::Vector2 screenSize;
	float scrollSpeed;
};

#endif // !BACKGROUND_SPRITE_COMPONENT_H