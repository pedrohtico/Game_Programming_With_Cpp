#ifndef ANIMATION_SPRITE_COMPONENT_H
#define ANIMATION_SPRITE_COMPONENT_H

#include "SpriteComponent.h"
#include <vector>
#include <SDL.h>

class AnimationSpriteComponent : public SpriteComponent
{
public:
	AnimationSpriteComponent(class Actor* owner, int drawOrder = 100);

	void Update(float deltaTime) override;

	void SetAnimationTextures(const std::vector<SDL_Texture*>& textures);

	float GetAnimationFPS() const { return animationFPS; }
	float SetAnimationFPS(const float fps) { this->animationFPS = fps; }
private:
	std::vector<SDL_Texture*> textures;
	float currentFrame;
	float animationFPS;
};

#endif // !ANIMATION_SPRITE_COMPONENT_H