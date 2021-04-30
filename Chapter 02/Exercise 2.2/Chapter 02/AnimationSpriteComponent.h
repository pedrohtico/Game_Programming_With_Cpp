#ifndef ANIMATION_SPRITE_COMPONENT_H
#define ANIMATION_SPRITE_COMPONENT_H

#include "SpriteComponent.h"
#include <vector>
#include <SDL.h>

#include <unordered_map>
#include "Math.h"

class AnimationSpriteComponent : public SpriteComponent
{
public:
	AnimationSpriteComponent(class Actor* owner, int drawOrder = 100);
	~AnimationSpriteComponent();

	void Update(float deltaTime) override;

	void SetAnimationTextures(const std::vector<SDL_Texture*>& textures);

	float GetAnimationFPS() const { return animationFPS; }
	void SetAnimationFPS(const float fps) { this->animationFPS = fps; }

	void AddAnimation(const std::string& name, const std::pair<int, int>& range, bool wrap);

	void SetCurrentAnimation(const std::string& anim_name);
	void SetCurrentAnimation(int index);

	std::string GetCurrentAnimation() const { return this->currentAnimation->animationName; }
private:
	struct Animation {
		std::string animationName;
		std::pair<int, int> range;
		bool wrap = true;
	};
	std::vector<SDL_Texture*> textures;
	std::vector<Animation*> animations;
	float currentFrame;
	float animationFPS;
	Animation* currentAnimation;
};

#endif // !ANIMATION_SPRITE_COMPONENT_H