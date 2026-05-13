#include "entities/Map.h"

Map::Map(GameContext& context, float scale) :
	tilemap(context.assetsManager.getTilemap()),
	scale(scale),
	context(context),
	TS(16)
{
	tilemap = context.assetsManager.getTilemap();
	tilemapSize = {
		static_cast<int>(tilemap[0].size()),
		static_cast<int>(tilemap.size())
	};

	mapOffset = calcOffset();

	sprites.resize(tilemap.size(), std::vector<sf::Sprite>(tilemap[0].size()));

	context.data.score = 0;
	int moneyCount = 0;

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
				moneyCount++;
				sprite.setTexture(context.assetsManager.getTexture("money"));
			}
			else if (tilemap[y][x] == tile::Gates) {
				sprite.setTexture(context.assetsManager.getTexture("gates"));
			}
			else if (tilemap[y][x] == tile::Enegrizer) {
				sprite.setTexture(context.assetsManager.getTexture("energizer"));
			}

			sprite.setPosition(x * TS, y * TS);

			sprites[y][x] = sprite;
		}
	}
	context.data.lastMoney = moneyCount;
}

void Map::handleEvent(const sf::Event& event) {
	
}

void Map::update(sf::RenderWindow& window, float dt) {
	mapOffset = calcOffset();

	if (!context.eventQueue.empty()) {
		GameEvent event = context.eventQueue.front();
		if (event.type == EventType::CoinCollected) {
			context.assetsManager.playSound("pickup");
			context.eventQueue.pop();
			tilemap[event.tilePos.y][event.tilePos.x] = tile::Void;
			sprites[event.tilePos.y][event.tilePos.x].setTexture(context.assetsManager.getTexture("void"));
			context.data.lastMoney--;
		}

		if (event.type == EventType::EnergizerCollected) {
			tilemap[event.tilePos.y][event.tilePos.x] = tile::Void;
			sprites[event.tilePos.y][event.tilePos.x].setTexture(context.assetsManager.getTexture("void"));
		}
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

		// T up
		else if (up && !down && left && right)
			return sf::IntRect({ 5 * TS, 0 * TS }, { TS, TS });

		// T вниз
		else if (!up && down && left && right)
			return sf::IntRect({ 5 * TS, 1 * TS }, { TS, TS });

		// T вправо
		else if (up && down && !left && right)
			return sf::IntRect({ 6 * TS, 0 * TS }, { TS, TS });

		// T влево
		else if (up && down && left && !right)
			return sf::IntRect({ 6 * TS, 1 * TS }, { TS, TS });

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


sf::Vector2i Map::posToGrid(sf::Vector2f pos) {
	sf::Vector2i sqrNum = {
		static_cast<int>(((pos.x - mapOffset.x)) / (TS * scale)),
		static_cast<int>(((pos.y - mapOffset.y)) / (TS * scale))
	};

	return sqrNum;
}

sf::Vector2f Map::gridToPos(sf::Vector2i pos) {
	sf::View view = context.window.getView();

	sf::Vector2f sqrNum = {
		static_cast<float>(pos.x * TS * scale + mapOffset.x + ((TS / 2) * scale)),
		static_cast<float>(pos.y * TS * scale + mapOffset.y + ((TS/2) * scale))
	};

	return sqrNum;
}

bool Map::isOnCenter(sf::Vector2f pos) {
	sf::Vector2f tileCenter = gridToPos(posToGrid(pos));
	sf::Vector2f delta = { 1.f, 1.f };

	sf::Vector2f distance = pos - tileCenter;

	return
		std::abs(distance.x) <= delta.x &&
		std::abs(distance.y) <= delta.y;
}

bool Map::isInHouse(sf::Vector2i pos) {
	return pos.y < tilemap.size() &&
		pos.x < tilemap[0].size() &&
		(tilemap[pos.y][pos.x] == tile::ClydeSpawn ||
		tilemap[pos.y][pos.x] == tile::PinkySpawn||
		tilemap[pos.y][pos.x] == tile::InkySpawn ||
		tilemap[pos.y][pos.x] == tile::Gates);
}

bool Map::isFree(sf::Vector2i pos) {
	return pos.y < tilemap.size() &&
		pos.x < tilemap[0].size() &&
		tilemap[pos.y][pos.x] != tile::Wall &&
		tilemap[pos.y][pos.x] != tile::Border;
};


bool Map::isFreeDirection(sf::Vector2i pos, MoveDirection dir) {
	sf::Vector2i checkingPos;
	switch (dir) {
	case MoveDirection::Up: {
		checkingPos = { pos.x, pos.y - 1 };
		break;
	}
	case MoveDirection::Down: {
		checkingPos = { pos.x, pos.y + 1 };
		break;
	}
	case MoveDirection::Left: {
		checkingPos = { pos.x - 1, pos.y };
		break;
	}
	case MoveDirection::Right: {
		checkingPos = { pos.x + 1, pos.y };
		break;
	}
	}
	return isFree(checkingPos);
}

bool Map::isMoney(sf::Vector2i pos) {
	return pos.y < tilemap.size() &&
		pos.x < tilemap[0].size() &&
		tilemap[pos.y][pos.x] == tile::Money;
};

bool Map::isEnergizer(sf::Vector2i pos) {
	return pos.y < tilemap.size() &&
		pos.x < tilemap[0].size() &&
		tilemap[pos.y][pos.x] == tile::Enegrizer;
}

bool Map::isTeleport(sf::Vector2i pos) {
	return pos.y < tilemap.size() &&
		pos.x < tilemap[0].size() &&
		tilemap[pos.y][pos.x] == tile::Teleport;
};


sf::Vector2i Map::getSingleTile(tile spawnTile) {
	for (int y = 0; y < tilemapSize.y; y++) {
		for (int x = 0; x < tilemapSize.x; x++) {
			if (tilemap[y][x] == spawnTile) {
				return {
					static_cast<int>(x), 
					static_cast<int>(y)
				};
			}
		}
	}
	Log::warn("TILE NOT FOUND");
	return { 0, 0 };
};