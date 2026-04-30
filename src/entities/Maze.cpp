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
			//sprite.setOrigin({ 8, 8 });
			if (tilemap[x][y] == tile::Wall) {
				sprite.setTexture(context.assetsManager.getTexture("mazeExt"));
				sprites[x][y] = sprite;
			}
			else if (tilemap[x][y] == tile::Border) {
				sprite.setTexture(context.assetsManager.getTexture("borderExt"));
				sprite.setTextureRect(calculateTile(x, y, tile::Border));
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

sf::IntRect Maze::calculateTile(int i, int j, tile tiletype) {
	switch (tiletype) {
		case tile::Wall:{
			break;
		}
		case tile::Border: {
			// Соседи текущего тайла
			bool up = (i > 0) && tilemap[i - 1][j] == tile::Border;
			bool down = (i + 1 < tilemap.size()) && tilemap[i + 1][j] == tile::Border;
			bool left = (j > 0) && tilemap[i][j - 1] == tile::Border;
			bool right = (j + 1 < tilemap[i].size()) && tilemap[i][j + 1] == tile::Border;

			int TS = 16;
			// ┌ левый верхний угол (есть справа и снизу)
			if (right && down && !left && !up)
				return sf::IntRect({ 0 * TS, 0 * TS }, { TS, TS });

			// │ вертикаль (есть сверху и снизу)
			else if (up && down && !left && !right)
				return sf::IntRect({ 1 * TS, 0 * TS }, { TS, TS });

			// └ левый нижний угол (есть справа и сверху)
			else if (right && up && !left && !down)
				return sf::IntRect({ 2 * TS, 0 * TS }, { TS, TS });


			// ─ горизонталь (есть слева и справа)
			else if (left && right && !up && !down)
				return sf::IntRect({ 0 * TS, 1 * TS }, { TS, TS });

			// ┐ правый верхний угол (есть слева и снизу)
			else if (left && down && !right && !up)
				return sf::IntRect({ 0 * TS, 2 * TS }, { TS, TS });

			// ┘ правый нижний угол (есть слева и сверху)
			else if (left && up && !right && !down)
				return sf::IntRect({ 2 * TS, 2 * TS }, { TS, TS });
			else
				return sf::IntRect({ 1 * TS, 1 * TS }, { TS, TS });
		}
	}
}