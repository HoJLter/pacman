#include "entities/Pacman.h"
#include "utils/Log.h"


Pacman::Pacman(GameContext& context,IMap& map, sf::Vector2u initPos, float scale) :
	context(context),
	scale(scale),
	map(map),
	speedPerSec(150.f),
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
				Log::debug("UP BUTTON");
				pacmanMove.changeRow(2);
				curDirection = MoveDirection::Up;
				break;
			}
			case sf::Keyboard::Down: {
				Log::debug("DOWN BUTTON");
				pacmanMove.changeRow(3);
				curDirection = MoveDirection::Down;
				break;
			}
			case sf::Keyboard::Left: {
				Log::debug("LEFT BUTTON");
				pacmanMove.changeRow(1);
				curDirection = MoveDirection::Left;
				break;
			}
			case sf::Keyboard::Right: {
				Log::debug("RIGHT BUTTON");
				pacmanMove.changeRow(0);
				curDirection = MoveDirection::Right;
				break;
			}
		}
	}
}
void Pacman::update(sf::RenderWindow& window, float dt) {
	sf::Vector2f curPosition = pacman.getPosition();
	sf::Vector2f newPosition = curPosition;

	switch (curDirection) {
	case MoveDirection::Up:
		newPosition.y -= speedPerSec * dt;
		break;

	case MoveDirection::Down:
		newPosition.y += speedPerSec * dt;
		break;

	case MoveDirection::Left:
		newPosition.x -= speedPerSec * dt;
		break;

	case MoveDirection::Right:
		newPosition.x += speedPerSec * dt;
		break;
	}


	float size = 16.0f * scale;
	float inset = 3.f * scale; 

	sf::Vector2f p1 = { newPosition.x - size / 2.f + inset, newPosition.y - size / 2.f + inset };
	sf::Vector2f p2 = { newPosition.x + size / 2.f - inset, newPosition.y - size / 2.f + inset };
	sf::Vector2f p3 = { newPosition.x - size / 2.f + inset, newPosition.y + size / 2.f - inset };
	sf::Vector2f p4 = { newPosition.x + size / 2.f - inset, newPosition.y + size / 2.f - inset };

	sf::Vector2u t1 = map.posToGrid(p1);
	sf::Vector2u t2 = map.posToGrid(p2);
	sf::Vector2u t3 = map.posToGrid(p3);
	sf::Vector2u t4 = map.posToGrid(p4);
	sf::Vector2u center = map.posToGrid(newPosition);


	if (map.isFree(t1) && map.isFree(t2) && map.isFree(t3) && map.isFree(t4)) {
		pacman.setPosition(newPosition);
	}

	if (map.isMoney(center)) {
		context.eventQueue.push(GameEvent{ EventType::CoinCollected, {center.x, center.y} });
		context.data.score += 20;
		Log::debug("Event CoinCollected has been pushed");
	};

	if (map.isTeleport(center)) {
		sf::Vector2u leftTpPos = { 0, 9 };
		sf::Vector2u rightTpPos = { 32, 9 };

		sf::Vector2u leftTpTarget = { 31, 9 };
		sf::Vector2u rightTpTarget = { 1, 9 };

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

sf::Vector2u Pacman::getCurPos() {
	return map.posToGrid(pacman.getPosition());
}