#include "Game.h"
#include "Actor.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"
#include <algorithm>
#include "SpriteComponent.h"

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->isRunning = true;
	this->ticksCounter = 0;
	this->isUpdatingActors = false;

	this->ship = nullptr;
}

// MAIN FUNCTIONS
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

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL image extension: %s", SDL_GetError());
		return false;
	}

	Random::Init();

	this->LoadData();

	this->ticksCounter = SDL_GetTicks();

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
	this->UnloadData();
	
	IMG_Quit();
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

// LOOP FUNCTIONS
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

	this->isUpdatingActors = true;
	for (auto& actor : this->actors)
		actor->ProcessInput(state);
	this->isUpdatingActors = false;

	if (state[SDL_SCANCODE_ESCAPE])
		this->isRunning = false;
}

void Game::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->ticksCounter + 16)) {} // frame limiting for 60 FPS

	float deltaTime = (SDL_GetTicks() - this->ticksCounter) / 1000.f; // SECONDS
	this->ticksCounter = SDL_GetTicks();

	if (deltaTime > 0.05f) // dt clamping
		deltaTime = 0.05f;

	// update actors
	this->isUpdatingActors = true;
	for (auto a : this->actors)
		a->Update(deltaTime);
	this->isUpdatingActors = false;

	for (auto pending : this->pendingActors)
		this->actors.emplace_back(pending);
	this->pendingActors.clear();

	std::vector<class Actor*> deadActors;
	for (auto actor : this->actors)
	{
		if (actor->GetState() == Actor::State::EDead)
			deadActors.emplace_back(actor);
	}
	for (auto dead : deadActors)
		delete dead;
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer); // clear back buffer

	for (auto s : this->sprites)
		s->Draw(this->renderer);

	SDL_RenderPresent(this->renderer); //swap buffers
}

// DATA HANDLING
void Game::LoadData()
{
	Ship* ship = new Ship(this);
	ship->SetPosition(Vector2(512.0f, 384.0f));
	ship->SetRotation(static_cast<float>(Math::PI / 2));

	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
		new Asteroid(this);
}

void Game::UnloadData()
{
	while (!this->actors.empty())
		delete this->actors.back();

	for (auto &t : this->textures)
		SDL_DestroyTexture(t.second);
	this->textures.clear();
}

// SPRITE FUNCTIONS
void Game::AddSprite(class SpriteComponent* sprite)
{
	auto iter = this->sprites.begin();
	for (; iter != this->sprites.end(); ++iter)
	{
		if (sprite->GetDrawOrder() < (*iter)->GetDrawOrder())
			break;
	}
	this->sprites.insert(iter, sprite);
}

void Game::RemoveSprite(class SpriteComponent* sprite)
{
	auto iter = std::find(this->sprites.begin(), this->sprites.end(), sprite);
	if (iter != this->sprites.end())
		this->sprites.erase(iter);
}

// TEXTURE FUNCTIONS
SDL_Texture* Game::GetTexture(const std::string& filename)
{
	auto iter = this->textures.find(filename);
	if (iter != this->textures.end()) // checks if texture is already loaded
		return iter->second;
	else
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			SDL_Log("Unable to create surface for '%s'", filename.c_str());
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
		if (!texture)
		{
			SDL_Log("Unable to create texture from surface '%s'", filename.c_str());
			return nullptr;
		}

		this->textures.emplace(filename.c_str(), texture);
		return texture;
	}
}

// ACTORS FUNCTIONS
void Game::AddActor(class Actor* actor)
{
	if (!this->isUpdatingActors)
		this->actors.emplace_back(actor);
	else
		this->pendingActors.emplace_back(actor);
}

void Game::RemoveActor(class Actor* actor)
{
	auto iter = std::find(this->pendingActors.begin(), this->pendingActors.end(), actor);
	if (iter != this->pendingActors.end())
	{
		std::iter_swap(iter, this->pendingActors.end() - 1);
		this->pendingActors.pop_back();
	}

	iter = std::find(this->actors.begin(), this->actors.end(), actor);
	if (iter != this->actors.end())
	{
		std::iter_swap(iter, this->actors.end() - 1);
		this->actors.pop_back();
	}
}

void Game::AddAsteroid(Asteroid* ast)
{
	this->asteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(this->asteroids.begin(), this->asteroids.end(), ast);
	if (iter != this->asteroids.end())
		this->asteroids.erase(iter);
}
