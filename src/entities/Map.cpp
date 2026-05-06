#include "entities/Map.h"

Map::Map(GameContext& context, float scale) :
	tilemap(context.assetsManager.getTilemap()),
	scale(scale),
	context(context)
{
	tilemap = context.assetsManager.getTilemap();
	tilemapSize = {
		static_cast<unsigned>(tilemap[0].size()),
		static_cast<unsigned>(tilemap.size())
	};

	sprites.resize(tilemap.size(), std::vector<sf::Sprite>(tilemap[0].size()));

	for (int y = 0; y < tilemap.size(); y++) {
		for (int x = 0; x < tilemap[0].size(); x++) {

			sf::Sprite sprite;
			sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));

			if (tilemap[y][x] == tile::Wall) {
				sprite.setTexture(context.assetsManager.getTexture("maze"));
				sprite.setTextureRect(calcWallType(y, x, tile::Wall));
			}
			else if (tilemap[y][x] == tile::Border) {
				sprite.setTexture(context.assetsManager.getTexture("border"));
				sprite.setTextureRect(calcWallType(y, x, tile::Border));
			}
			else if (tilemap[y][x] == tile::Money) {
				sprite.setTexture(context.assetsManager.getTexture("money"));
			}

			sprite.setPosition(x * 16, y * 16);

			sprites[y][x] = sprite;
		}
	}
}

void Map::handleEvent(const sf::Event& event) {
	
}

void Map::update(sf::RenderWindow& window, float dt) {
	if (!context.eventQueue.empty()) {
		GameEvent& event = context.eventQueue.front();
		if (event.type == EventType::CoinCollected) {
			Log::debug("Event CoinCollected has been catcherd");
			context.eventQueue.pop();
		
			tilemap[event.tilePos.y][event.tilePos.x] = tile::Void;
			sprites[event.tilePos.y][event.tilePos.x].setTexture(context.assetsManager.getTexture("void"));
		}
		tilemap = context.assetsManager.getTilemap();
	}
}

void Map::render(sf::RenderWindow& window) {
	int tileSize = 16;

	int mapWidth = tilemap[0].size();
	int mapHeight = tilemap.size();

	sf::View view = window.getView();
	sf::Vector2f viewSize = view.getSize();

	float mapPixelWidth = mapWidth * tileSize * scale;
	float mapPixelHeight = mapHeight * tileSize * scale;

	offsetX = (viewSize.x - mapPixelWidth) / 2.0f;
	offsetY = (viewSize.y - mapPixelHeight) / 2.0f;

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			sprites[y][x].setPosition({
				offsetX + x * tileSize * scale,
				offsetY + y * tileSize * scale
				});

			sprites[y][x].setScale({ scale, scale });
			window.draw(sprites[y][x]);
		}
	}
}

sf::IntRect Map::calcWallType(int i, int j, tile tiletype) {
	switch (tiletype) {
	case tile::Wall: {
		bool up = (i > 0) && tilemap[i - 1][j] == tile::Wall;
		bool down = (i + 1 < tilemap.size()) && tilemap[i + 1][j] == tile::Wall;
		bool left = (j > 0) && tilemap[i][j - 1] == tile::Wall;
		bool right = (j + 1 < tilemap[i].size()) && tilemap[i][j + 1] == tile::Wall;

		int TS = 16;

		if (right && !left && !up && !down)
			return sf::IntRect({ 0 * TS, 0 * TS }, { TS, TS });

		// ─ горизонталь
		else if (!up && !down && left && right)
			return sf::IntRect({ 1 * TS, 0 * TS }, { TS, TS });

		// ─ правый конец: линия идёт влево
		else if (left && !right && !up && !down)
			return sf::IntRect({ 2 * TS, 0 * TS }, { TS, TS });


		// │ верхний конец: линия идёт вниз
		else if (down && !up && !left && !right)
			return sf::IntRect({ 0 * TS, 1 * TS }, { TS, TS });

		// │ вертикаль
		else if (up && down && !left && !right)
			return sf::IntRect({ 1 * TS, 1 * TS }, { TS, TS });

		// │ нижний конец: линия идёт вверх
		else if (up && !down && !left && !right)
			return sf::IntRect({ 2 * TS, 1 * TS }, { TS, TS });


		// угол, соединяет ВПРАВО + ВНИЗ
		else if (right && down && !left && !up)
			return sf::IntRect({ 3 * TS, 0 * TS }, { TS, TS });

		// угол, соединяет ВЛЕВО + ВНИЗ
		else if (left && down && !right && !up)
			return sf::IntRect({ 4 * TS, 0 * TS }, { TS, TS });

		// угол, соединяет ВПРАВО + ВВЕРХ
		else if (right && up && !left && !down)
			return sf::IntRect({ 3 * TS, 1 * TS }, { TS, TS });

		// угол, соединяет ВЛЕВО + ВВЕРХ
		else if (left && up && !right && !down)
			return sf::IntRect({ 4 * TS, 1 * TS }, { TS, TS });

		else {
			return sf::IntRect({ 1 * TS, 1 * TS }, { TS, TS });
		}
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
				return sf::IntRect({ 0 * TS, 1 * TS }, { TS, TS });

			// └ левый нижний угол (есть справа и сверху)
			else if (right && up && !left && !down)
				return sf::IntRect({ 0 * TS, 2 * TS }, { TS, TS });


			// ─ горизонталь (есть слева и справа)
			else if (left && right && !up && !down)
				return sf::IntRect({ 1 * TS, 0 * TS }, { TS, TS });

			// ┐ правый верхний угол (есть слева и снизу)
			else if (left && down && !right && !up)
				return sf::IntRect({ 2 * TS, 0 * TS }, { TS, TS });

			// ┘ правый нижний угол (есть слева и сверху)
			else if (left && up && !right && !down)
				return sf::IntRect({ 2 * TS, 2 * TS }, { TS, TS });
			else
				return sf::IntRect({ 1 * TS, 1 * TS }, { TS, TS });
		}
	}
}


sf::Vector2u Map::posToGrid(sf::Vector2f pos) {
	sf::Vector2u sqrNum = {
		static_cast<unsigned>(((pos.x - offsetX)) / (TS * scale)),
		static_cast<unsigned>(((pos.y - offsetY)) / (TS * scale))
	};

	return sqrNum;
}

sf::Vector2f Map::gridToPos(sf::Vector2u pos) {
	sf::Vector2f sqrNum = {
		static_cast<float>(pos.x * TS * scale + offsetX + ((TS / 2) * scale)),
		static_cast<float>(pos.y * TS * scale + offsetY + ((TS/2) * scale))
	};

	return sqrNum;
}