#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL.h>

// 2d vector
struct Vector2 { float x, y; };

struct Ball { Vector2 Pos, Vel; };

class Game
{
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	Vector2 paddlePos;
	int paddleDir;

	Vector2 paddle2Pos;
	int paddle2Dir;

	std::vector<Ball> balls;

private:
	// helper functions for game loop
	void ProcessInput();
	void Update();
	void GenerateOutput();

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
	Uint32 ticksCounter;
};

#endif // !GAME_H