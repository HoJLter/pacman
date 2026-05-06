#include "entities/Map.h"

Map::Map(GameContext& context, float scale) :
	tilemap(context.assetsManager.getTilemap()),
	scale(scale),
	context(context),
	TS(16)
{
	tilemap = context.assetsManager.getTilemap();
	tilemapSize = {
		static_cast<unsigned>(tilemap[0].size()),
		static_cast<unsigned>(tilemap.size())
	};

	mapOffset = calcOffset();

	sprites.resize(tilemap.size(), std::vector<sf::Sprite>(tilemap[0].size()));

	for (int y = 0; y < tilemap.size(); y++) {
		for (int x = 0; x < tilemap[0].size(); x++) {

			sf::Sprite sprite;
			sprite.setTextureRect(sf::IntRect({ 0, 0 }, { TS, TS }));

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

			sprite.setPosition(x * TS, y * TS);

			sprites[y][x] = sprite;
		}
	}
}

void Map::handleEvent(const sf::Event& event) {
	
}

void Map::update(sf::RenderWindow& window, float dt) {
	mapOffset = calcOffset();

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
	for (int y = 0; y < tilemapSize.y; y++) {
		for (int x = 0; x < tilemapSize.x; x++) {
			sprites[y][x].setPosition({
				mapOffset.x + x * TS * scale,
				mapOffset.y + y * TS * scale
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


sf::Vector2f Map::calcOffset() {
	sf::View view = context.window.getView();

	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();

	sf::Vector2f viewOffset = { 
		viewCenter.x - (viewSize.x / 2.f),
		viewCenter.y - (viewSize.y / 2.f)
	};

	sf::Vector2f mapSize = {
		tilemap[0].size() * TS * scale,
		tilemap.size() * TS * scale
	}; 
	
	sf::Vector2f mapOffset = {
		(viewOffset.x + ((viewSize.x - mapSize.x) / 2.f)),
		(viewOffset.y + ((viewSize.y - mapSize.y) / 2.f))
	};

	return mapOffset;
}


sf::Vector2u Map::posToGrid(sf::Vector2f pos) {
	sf::Vector2u sqrNum = {
		static_cast<unsigned>(((pos.x - mapOffset.x)) / (TS * scale)),
		static_cast<unsigned>(((pos.y - mapOffset.y)) / (TS * scale))
	};

	return sqrNum;
}

sf::Vector2f Map::gridToPos(sf::Vector2u pos) {
	sf::View view = context.window.getView();

	sf::Vector2f sqrNum = {
		static_cast<float>(pos.x * TS * scale + mapOffset.x + ((TS / 2) * scale)),
		static_cast<float>(pos.y * TS * scale + mapOffset.y + ((TS/2) * scale))
	};

	return sqrNum;
}


bool Map::isFree(sf::Vector2u pos) {
	return pos.y < tilemap.size() &&
		pos.x < tilemap[0].size() &&
		tilemap[pos.y][pos.x] != tile::Wall &&
		tilemap[pos.y][pos.x] != tile::Border;
};

bool Map::isMoney(sf::Vector2u pos) {
	return pos.y < tilemap.size() &&
		pos.x < tilemap[0].size() &&
		tilemap[pos.y][pos.x] == tile::Money;
};

bool Map::isTeleport(sf::Vector2u pos) {
	return pos.y < tilemap.size() &&
		pos.x < tilemap[0].size() &&
		tilemap[pos.y][pos.x] == tile::Teleport;
};


sf::Vector2u Map::getSingleTile(tile spawnTile) {
	for (int y = 0; y < tilemapSize.y; y++) {
		for (int x = 0; x < tilemapSize.x; x++) {
			if (tilemap[y][x] == spawnTile) {
				return {
					static_cast<unsigned>(y), 
					static_cast<unsigned>(x)
				};
			}
		}
	}
	return { 0, 0 };
};