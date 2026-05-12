#include "entities/Ghost.h"
#include "utils/Log.h"
#include "engine/core/Algorithms.h"
#include <algorithm>



Ghost::Ghost(GameContext& context, IMap& map, GhostType type, sf::Vector2u initPos, float scale):
	context(context),
	map(map),
	ghostType(type),
	scale(scale),
	speedPerSec(200.f),
	ghostMoveTexture(context.assetsManager.getTexture(mapGhostType(type))),
	ghostMoveAnimation(
		ghostMoveTexture, // texture
		2,                 // frames
		16,                // frameWidth
		16,                // frameHeight
		0,                 // row
		0.1f			   // animation speed (in seconds)
	)
{
	curDirection = MoveDirection::None;
	Log::debug(mapGhostType(type) + " has been created. X: " + std::to_string(initPos.x) + " Y: " + std::to_string(initPos.y));
	ghost.setOrigin(8.f, 8.f);
	ghost.setTexture(ghostMoveTexture);
	ghost.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
	ghost.setPosition(map.gridToPos(initPos));
	ghost.setScale({ scale, scale });
}

void Ghost::handleEvent(const sf::Event& event) {

}

void Ghost::update(sf::RenderWindow& window, 
	sf::Vector2u pacmanPos, 
	MoveDirection pacmanDir, 
	sf::Vector2u blinkyPos, 
	float dt) 
{
	if (curMode == Mode::Scatter &&
		modeClock.getElapsedTime().asSeconds() > 7.f) {
		modeClock.restart();
		curMode = Mode::Chase;
	}
	else if (curMode == Mode::Chase &&
		modeClock.getElapsedTime().asSeconds() > 20.f) {
		modeClock.restart();
		curMode = Mode::Scatter;
	}

	sf::Vector2u target = updateTarget(pacmanPos, blinkyPos, pacmanDir);
	if (isOnCross()) {
		std::vector<MoveDirection> freeDirs;
		std::vector<MoveDirection> dirs = {
			MoveDirection::Down, MoveDirection::Up,
			MoveDirection::Left, MoveDirection::Right
		};

		for (auto dir : dirs) {
			if (map.isFreeDirection(map.posToGrid(ghost.getPosition()), dir)) {
				freeDirs.push_back(dir);
			}
		}
	}
	ghostMoveAnimation.update(dt);
	ghostMoveAnimation.applyToSprite(ghost);
}

void Ghost::render(sf::RenderWindow& window) {
	window.draw(ghost);
}


MoveDirection Ghost::chooseNextDirection(sf::Vector2u target) {
	sf::Vector2u curPosition = map.posToGrid(ghost.getPosition());

	sf::Vector2i up = { 0, -1 };
	sf::Vector2i left = { -1, 0 };
	sf::Vector2i down = { 0, 1 };
	sf::Vector2i right = { 1, 0 };
	
	std::vector<sf::Vector2i> dirs = { up, left, down, right };

	float bestDist = 10000.f;
	MoveDirection bestDir;
	for (auto dir : dirs) {
		sf::Vector2 nextTile = {
			curPosition.x + dir.x,
			curPosition.y + dir.y
		};
		if (!map.isFree(nextTile) || nextTile == curPosition) {
			continue;
		}
		float distance = calcDistance(nextTile, target);

		if (distance < bestDist) {
			bestDist = distance;
			if (dir == up) {
				bestDir = MoveDirection::Up;
			}
			else if (dir == down) {
				bestDir = MoveDirection::Down;
			}
			else if (dir == left) {
				bestDir = MoveDirection::Left;
			}
			else if (dir == right) {
				bestDir = MoveDirection::Right;
			}
		}
	}
	return bestDir;
}


// TARGETS

sf::Vector2u Ghost::calcBlinkyTarget(sf::Vector2u pacmanPos, MoveDirection pacmanDir) {
	sf::Vector2u target;
	return pacmanPos;
}


sf::Vector2u Ghost::calcPinkyTarget(sf::Vector2u pacmanPos, MoveDirection pacmanDir) {
	sf::Vector2u target;
	int offset = 4;

	int newX = static_cast<int>(pacmanPos.x);
	int newY = static_cast<int>(pacmanPos.y);

	switch (pacmanDir) {
	case MoveDirection::Up:    newY -= offset; break;
	case MoveDirection::Down:  newY += offset; break;
	case MoveDirection::Left:  newX -= offset; break;
	case MoveDirection::Right: newX += offset; break;
	default: break;
	}

	newX = std::max(newX, 0);
	newY = std::max(newY, 0);

	return {
		static_cast<unsigned int>(newX),
		static_cast<unsigned int>(newY)
	};
}


sf::Vector2u Ghost::calcInkyTarget(sf::Vector2u pacmanPos, sf::Vector2u blinkyPos,  MoveDirection pacmanDir) {
	int offset = 2;

	int targetX = static_cast<int>(pacmanPos.x);
	int targetY = static_cast<int>(pacmanPos.y);

	switch (pacmanDir) {
	case MoveDirection::Up:    targetY -= offset; break;
	case MoveDirection::Down:  targetY += offset; break;
	case MoveDirection::Left:  targetX -= offset; break;
	case MoveDirection::Right: targetX += offset; break;
	default: break;
	}

	//targetX taretY на две позиции впереди пакмана
	targetX = std::max(targetX, 0);
	targetY = std::max(targetY, 0);

	int vecX = targetX - blinkyPos.x;
	int vecY = targetY - blinkyPos.y;

	int finalX = blinkyPos.x + 2 * vecX;
	int finalY = blinkyPos.y + 2 * vecY;

	return {
		static_cast<unsigned>(finalX),
		static_cast<unsigned>(finalY)};
}


sf::Vector2u Ghost::calcClydeTarget(sf::Vector2u pacmanPos, MoveDirection pacmanDir) {
	sf::Vector2u target;

	if (calcDistance(pacmanPos, map.posToGrid(ghost.getPosition())) > 8) {
		target = pacmanPos;
	}
	else {
		target = map.getSize();
	}
	return target;
}


sf::Vector2u Ghost::updateTarget(sf::Vector2u pacmanPos, sf::Vector2u blinkyPos, MoveDirection pacmanDir) {
	sf::Vector2u target;
	switch (ghostType) {
		case GhostType::Blinky: {
			target = calcBlinkyTarget(pacmanPos, pacmanDir);
			break;
		}
		case GhostType::Pinky: {
			target = calcPinkyTarget(pacmanPos, pacmanDir);
			break;
		}
		case GhostType::Inky: {
			target = calcInkyTarget(pacmanPos, blinkyPos, pacmanDir);
			break;
		}
		case GhostType::Clyde: {
			target = calcClydeTarget(pacmanPos, pacmanDir);
			break;
		}
	}

	if (logClock.getElapsedTime().asSeconds() > 5.f) {
		logClock.restart();
		Log::debug(mapGhostType(ghostType) + "'s target: X: " + std::to_string(target.x) + " Y: " + std::to_string(target.y));
	}
	return target;
}

sf::Vector2u Ghost::getCurPos() {
	return map.posToGrid(ghost.getPosition());
}	