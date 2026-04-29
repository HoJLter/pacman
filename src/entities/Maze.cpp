#include "entities/Maze.h"

Maze::Maze(GameContext& context) {
	tilemap = context.assetsManager.getTilemap();
	sprites.resize(std::vector<sf::Sprite>(), tilemap.size());
	for (int x = 0; x < tilemap.size(); x ++) {
		for (int y = 0; y < tilemap[0].size(); y++) {
			if (tilemap[x, y] == tile::Wall) {
				sprites[x,y] == 
			}
		}
	}
}