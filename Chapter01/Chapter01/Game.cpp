#include "Game.h"

const int THICKNESS = 15;
const float PADDLE_HEIGHT = 100.f;
const int NUM_BALLS = 5;

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;

	this->paddlePos = { 10, 360 };
	this->paddleDir = 0;

	this->paddle2Pos = { 1014 - THICKNESS, 360 };
	this->paddle2Dir = 0;

	for (int i = 0; i < NUM_BALLS; i++)
	{
		Ball b;
		b.Pos.x = rand() % 513 + 256;
		b.Pos.y = rand() % 361 + 180;
		b.Vel = { -200.f, 235.f };
		this->balls.push_back(b);
	}

	this->isRunning = true;
	this->ticksCounter = 0;
}

bool Game::Initialize()
{
	int init = SDL_Init(SDL_INIT_VIDEO);
	if (init != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	this->window = SDL_CreateWindow("Chapter 01", 120, 35, 1024, 720, 0);
	if (!this->window)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}

	this->renderer = SDL_CreateRenderer(
		this->window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!this->renderer)
	{
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::RunLoop()
{
	while (this->isRunning)
	{
		this->ProcessInput();
		this->Update();
		this->GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->isRunning = false;
			break;
		default:
			break;
		}
	}

	// keyboard inputs
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
		this->isRunning = false;

	// paddle 1 movement
	paddleDir = 0;
	if (state[SDL_SCANCODE_W])
		paddleDir += -1;

	if (state[SDL_SCANCODE_S])
		paddleDir += 1;

	// paddle 2 movement
	paddle2Dir = 0;
	if (state[SDL_SCANCODE_UP])
		paddle2Dir += -1;

	if (state[SDL_SCANCODE_DOWN])
		paddle2Dir += 1;

}

void Game::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->ticksCounter + 16)) {} // frame limiting for 60 FPS

	float deltaTime = (SDL_GetTicks() - this->ticksCounter) / 1000.f; // dt in seconds
	this->ticksCounter = SDL_GetTicks();

	if (deltaTime > 0.05f) // dt clamping
		deltaTime = 0.05f;

	// paddles boundaries
	if (this->paddleDir != 0)
	{
		this->paddlePos.y += this->paddleDir * 300.f * deltaTime; // update paddle position

		if (this->paddlePos.y < PADDLE_HEIGHT / 2.f + THICKNESS) // UPPER BOUNDARY
			this->paddlePos.y = PADDLE_HEIGHT / 2.f + THICKNESS;
		else if (this->paddlePos.y > 720 - PADDLE_HEIGHT / 2.f - THICKNESS) // BOTTOM BOUNDARY
			this->paddlePos.y = 720 - PADDLE_HEIGHT / 2.f - THICKNESS;
	}

	if (this->paddle2Dir != 0)
	{
		this->paddle2Pos.y += this->paddle2Dir * 300.f * deltaTime; // update paddle 2 position

		if (this->paddle2Pos.y < PADDLE_HEIGHT / 2.f + THICKNESS) // UPPER
			this->paddle2Pos.y = PADDLE_HEIGHT / 2.f + THICKNESS;
		else if (this->paddle2Pos.y > 720 - PADDLE_HEIGHT / 2.f - THICKNESS) // BOTTOM
			this->paddle2Pos.y = 720 - PADDLE_HEIGHT / 2.f - THICKNESS;
	}

	for (Ball& b : this->balls)
	{
		// ball boundaries
		b.Pos.x += b.Vel.x * deltaTime;  //  update ball  
		b.Pos.y += b.Vel.y * deltaTime;  //  position
		if (b.Pos.y <= 1.5f * THICKNESS && b.Vel.y < 0.f) // UPPER BOUNDARY
			b.Vel.y *= -1.f;
		else if (b.Pos.y > 720 - 1.5f * THICKNESS && b.Vel.y > 0.f) // BOTTOM BOUNDARY
			b.Vel.y *= -1.f;

		// ball and paddle 1 collision
		float diff = b.Pos.y - paddlePos.y; // y position difference
		if (diff < 0) diff *= -1; // absolute value of y difference

		if (diff <= PADDLE_HEIGHT / 2.f && // y position collides
			b.Pos.x >= 10.f + THICKNESS / 2.f && // x position
			b.Pos.x <= 25.f + THICKNESS / 2.f && // collides
			b.Vel.x < 0.f) // ball is moving left
		{
			b.Vel.x *= -1.f;
		}
		else
		{
			// ball and paddle 2 collision
			diff = b.Pos.y - paddle2Pos.y;
			if (diff < 0) diff *= -1;

			if (diff <= PADDLE_HEIGHT / 2.f &&
				b.Pos.x >= this->paddle2Pos.x - THICKNESS / 2.f &&
				b.Pos.x <= this->paddle2Pos.x + 1.5f * THICKNESS &&
				b.Vel.x > 0.f)
			{
				b.Vel.x *= -1;
			}
		}

		// if out of horizontal boundaries, reset ball to center
		if (b.Pos.x < 0 || b.Pos.x > 1024)
		{
			b.Pos = { 512, 360 };
			b.Vel = { 200.f, -235.f };
		}
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255);
	SDL_RenderClear(this->renderer); // clear back buffer

	// draw walls
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	SDL_Rect wall { 0, 0, 1024, THICKNESS }; // UPPER WALL
	SDL_RenderFillRect(this->renderer, &wall);

	wall.y = 720 - THICKNESS; // BOTTOM WALL
	SDL_RenderFillRect(this->renderer, &wall);

	// draw balls
	SDL_Rect ball;
	for (Ball& b : this->balls)
	{
		ball = {
			static_cast<int>(b.Pos.x - THICKNESS / 2),
			static_cast<int>(b.Pos.y - THICKNESS / 2),
			THICKNESS,
			THICKNESS
		};
		SDL_RenderFillRect(this->renderer, &ball);
	}

	// draw paddles
	SDL_Rect paddle = { // LEFT PADDLE
		static_cast<int>(this->paddlePos.x),
		static_cast<int>(this->paddlePos.y - PADDLE_HEIGHT / 2.f),
		THICKNESS,
		static_cast<int>(PADDLE_HEIGHT)
	};
	SDL_RenderFillRect(this->renderer, &paddle);

	paddle = { // RIGHT PADDLE
		static_cast<int>(this->paddle2Pos.x),
		static_cast<int>(this->paddle2Pos.y - PADDLE_HEIGHT / 2.f),
		THICKNESS,
		static_cast<int>(PADDLE_HEIGHT)
	};
	SDL_RenderFillRect(this->renderer, &paddle);

	SDL_RenderPresent(this->renderer); // swap buffers
}
