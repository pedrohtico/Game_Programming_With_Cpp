#include "TileMapComponent.h"
#include "Actor.h"
#include "Game.h"

#include <iostream>
#include <fstream>
#include <sstream>

TileMapComponent::TileMapComponent(class Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
{
	SDL_Texture* texture = this->owner->GetGame()->GetTexture("Assets/Tiles.png");
	this->SetTexture(texture);
}

void TileMapComponent::ReadTileSet(const std::string& filename)
{
	std::vector<int> row;
	std::string line, word;

	std::fstream file(filename, std::ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();
			std::stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(std::stoi(word.c_str()));
			this->tileMap.push_back(row);
		}
	}
	else
	{
		std::cout << "Couldn't open tile layer map" << std::endl;
	}
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	if (this->texture)
	{	
		int tileSize = 32;
		int i = 0;
		for (auto &row : this->tileMap)
		{
			int j = 0;
			for (auto& key : row)
			{
				SDL_Rect tilePos = { 0, 0, 0, 0 };
				tilePos.w = static_cast<int>(tileSize * this->owner->GetScale()); // SPRITE WIDTH
				tilePos.h = static_cast<int>(tileSize * this->owner->GetScale()); // SPRITE HEIGHT
			
				tilePos.x = static_cast<int>(j * tileSize); // SPRITE X POS
				tilePos.y = static_cast<int>(i * tileSize); // SPRITE Y POS

				SDL_Rect textureRect = { 0, 0, 0, 0};
				textureRect.w = static_cast<int>(tileSize * this->owner->GetScale());
				textureRect.h = static_cast<int>(tileSize * this->owner->GetScale());
				if (this->tileMap[i][j] != -1)
				{
					textureRect.x = (this->tileMap[i][j] % 8) * tileSize;
					textureRect.y = static_cast<int>((this->tileMap[i][j] / 8)) * tileSize;
				}

				SDL_RenderCopyEx(
					renderer,
					this->texture,
					&textureRect,
					&tilePos,
					Math::RadiansToDegree(this->owner->GetRotation()),
					nullptr,
					SDL_FLIP_NONE);

				j++;
			}

			i++;
		}
	}
}