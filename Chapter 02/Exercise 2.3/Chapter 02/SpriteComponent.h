#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Component.h"
#include <SDL.h>

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void SetTexture(SDL_Texture* texture);
	virtual void Draw(SDL_Renderer* renderer);

	// Getters
	int GetDrawOrder() const { return drawOrder; }
	int GetTextureWidth() const { return textureWidth; }
	int GetTextureHeight() const { return textureHeight; }
protected:
	SDL_Texture* texture;

	int drawOrder; // order for painter's algorithm | lower number, further back

	int textureWidth;
	int textureHeight;
};

#endif // !SPRITE_COMPONENT_H