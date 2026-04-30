#include "entities/Maze.h"

Maze::Maze(GameContext& context, float scale):
	tilemap(context.assetsManager.getTilemap()),
	scale(scale)
{
	tilemap = context.assetsManager.getTilemap();
	sprites.resize(tilemap.size(), std::vector<sf::Sprite>(tilemap[0].size(), {}));
	
	for (int x = 0; x < tilemap.size(); x ++) {
		for (int y = 0; y < tilemap[0].size(); y++) {
			sf::Sprite sprite;
			sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
			if (tilemap[x][y] == tile::Wall) {
				sprite.setTexture(context.assetsManager.getTexture("mazeExt"));
				sprites[x][y] = sprite;
			}
			else if (tilemap[x][y] == tile::Border) {
				sprite.setTexture(context.assetsManager.getTexture("borderExt"));
				sprites[x][y] = sprite;
			}
			else if (tilemap[x][y] == tile::Money) {
				sprite.setTexture(context.assetsManager.getTexture("money"));
				sprites[x][y] = sprite;

			}
		}
	}
}


void Maze::handleEvent(const sf::Event& event) {
	
}

void Maze::update(sf::RenderWindow& window, float dt) {

}

void Maze::render(sf::RenderWindow& window) {
	for (int x = 0; x < tilemap.size(); x++){
		for (int y = 0; y < tilemap[0].size(); y++) {
			sprites[x][y].setPosition(x * 16*scale, y * 16*scale);
			sprites[x][y].setScale({scale, scale});
			window.draw(sprites[x][y]);
		}
	}
}