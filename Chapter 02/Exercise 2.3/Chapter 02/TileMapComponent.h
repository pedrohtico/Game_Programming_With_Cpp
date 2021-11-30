#ifndef TILE_MAP_COMPONENT_H
#define TILE_MAP_COMPONENT_H

#include "SpriteComponent.h"
#include <string>
#include <vector>

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 10);

	void ReadTileSet(const std::string& filename);
	void Draw(SDL_Renderer* renderer) override;

private:
	std::vector<std::vector<int>> tileMap;
};

#endif // !TILE_MAP_COMPONENT_H
