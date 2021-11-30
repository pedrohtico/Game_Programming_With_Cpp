#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
	Game();

	// main functions
	bool Initialize();
	void RunLoop();
	void Shutdown();

	// sprite functions
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	// texture functions
	SDL_Texture* GetTexture(const std::string& filename);

	// actor functions
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

private:
	// helper functions for game loop
	void ProcessInput();
	void Update();
	void GenerateOutput();

	// SDL variables
	SDL_Window* window;
	SDL_Renderer* renderer;

	// loop variables
	bool isRunning;
	Uint32 ticksCounter; // number of ticks since game run until start of current frame

	// data handling
	void LoadData();
	void UnloadData();

	// sprites vector
	std::vector<class SpriteComponent*> sprites;

	// texture vector
	std::unordered_map<std::string, SDL_Texture*> textures;

	// actors
	std::vector<class Actor*> actors, pendingActors;
	bool isUpdatingActors;
};

#endif // !GAME_H