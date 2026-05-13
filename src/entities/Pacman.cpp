#include "entities/Pacman.h"
#include "utils/Log.h"


Pacman::Pacman(GameContext& context,IMap& map, sf::Vector2i initPos, float scale) :
	context(context),
	scale(scale),
	map(map),
	speedPerSec(650.f),
	pacmanMoveTexture(context.assetsManager.getTexture("pacmanMove")),
	pacmanMove(
		pacmanMoveTexture, // texture
		2,                 // frames
		16,                // frameWidth
		16,                // frameHeight
		0,                 // row
		0.1f			   // animation speed (in seconds)
	)
{
	curDirection = MoveDirection::None;
	Log::debug("Pacman has been created");
	pacman.setTexture(pacmanMoveTexture);
	pacman.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
	pacman.setPosition(map.gridToPos(initPos));
	pacman.setOrigin(8.f, 8.f);
	pacman.setScale({ scale, scale });
}

void Pacman::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			case sf::Keyboard::Up: {
				nextDirection = MoveDirection::Up;
				break;
			}
			case sf::Keyboard::Down: {
				nextDirection = MoveDirection::Down;
				break;
			}
			case sf::Keyboard::Left: {
				nextDirection = MoveDirection::Left;				
				break;
			}
			case sf::Keyboard::Right: {
				nextDirection = MoveDirection::Right;
				break;
			}
		}
	}
}


void Pacman::update(sf::RenderWindow& window, float dt) {
	sf::Vector2f curPosition = pacman.getPosition();
	sf::Vector2i gridPos = map.posToGrid(curPosition);

	

	pacmanMove.changeRow(chooseAnimRow());
	if (map.isOnCenter(curPosition)) {
		if (map.isFreeDirection(gridPos, nextDirection)) {
			curDirection = nextDirection;
		}
		else if (!map.isFreeDirection(gridPos, curDirection)) {
			curDirection = MoveDirection::None;
		}
	}

	if (curDirection != MoveDirection::None) {
		sf::Vector2i moveVector = dirToVector(curDirection);

		pacman.move({
			moveVector.x * speedPerSec * dt,
			moveVector.y * speedPerSec * dt
			});
	}

	sf::Vector2i center = gridPos;

	if (map.isMoney(center)) {
		context.eventQueue.push(GameEvent{ EventType::CoinCollected, {center.x, center.y} });
		context.data.score += 20;
		Log::debug("Event CoinCollected has been pushed");
	};

	if (map.isEnergizer(center)) {
		context.eventQueue.push(GameEvent{ EventType::EnergizerCollected, {center.x, center.y} });
	};

	if (map.isTeleport(center)) {
		sf::Vector2i leftTpPos = { 0, 9 };
		sf::Vector2i rightTpPos = { 32, 9 };

		sf::Vector2i leftTpTarget = { 31, 9 };
		sf::Vector2i rightTpTarget = { 1, 9 };

		if (center.x == leftTpPos.x &&
			center.y == leftTpPos.y) {
			Log::debug("Left teleport has been used");
			pacman.setPosition(map.gridToPos(leftTpTarget));
		}
		else if (center.x == rightTpPos.x &&
			center.y == rightTpPos.y) {
			Log::debug("Right teleport has been used");
			pacman.setPosition(map.gridToPos(rightTpTarget));
		}
	}

	pacmanMove.update(dt);
	pacmanMove.applyToSprite(pacman);
}


void Pacman::render(sf::RenderWindow& window) {
	window.draw(pacman);
}

sf::Vector2i Pacman::getCurPos() {
	return map.posToGrid(pacman.getPosition());
}

int Pacman::chooseAnimRow() {
	switch (curDirection) {
		case MoveDirection::Up:   return 2;
		case MoveDirection::Down: return 3;
		case MoveDirection::Left: return 1;
		case MoveDirection::Right:return 0;
	}
	return 3;
}