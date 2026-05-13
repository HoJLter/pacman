#include "entities/Ghost.h"
#include "utils/Log.h"
#include "engine/core/Algorithms.h"


sf::Vector2i Ghost::calcBlinkyTarget(sf::Vector2i pacmanPos, MoveDirection pacmanDir) {
	sf::Vector2i target;
	return pacmanPos;
}


sf::Vector2i Ghost::calcPinkyTarget(sf::Vector2i pacmanPos, MoveDirection pacmanDir) {
	sf::Vector2i target;
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
		(newX),
		(newY)
	};
}


sf::Vector2i Ghost::calcInkyTarget(sf::Vector2i pacmanPos, sf::Vector2i blinkyPos, MoveDirection pacmanDir) {
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
		(finalX),
		(finalY) };
}


sf::Vector2i Ghost::calcClydeTarget(sf::Vector2i pacmanPos, MoveDirection pacmanDir) {
	sf::Vector2i target;

	if (calcDistance(pacmanPos, map.posToGrid(ghost.getPosition())) > 8) {
		target = pacmanPos;
	}
	else {
		target = map.getSize();
	}
	return target;
}


sf::Vector2i Ghost::updateTarget(sf::Vector2i pacmanPos, sf::Vector2i blinkyPos, MoveDirection pacmanDir) {
	sf::Vector2i target;
	switch (ghostType) {
	case GhostType::Blinky: {
		if (curMode == Mode::Scatter) {
			target = {1, 1};
		}
		else {
			target = calcBlinkyTarget(pacmanPos, pacmanDir);
		}
		break;
	}
	case GhostType::Pinky: {
		if (curMode == Mode::Scatter) {
			target = { 31, 1 };
		}
		else {
			target = calcPinkyTarget(pacmanPos, pacmanDir);
		}
		break;
	}
	case GhostType::Inky: {
		if (curMode == Mode::Scatter) {
			target = { 1, 16 };
		}
		else {
			target = calcInkyTarget(pacmanPos, blinkyPos, pacmanDir);
		}
		break;
	}
	case GhostType::Clyde: {
		if (curMode == Mode::Scatter) {
			target = { 31, 16 };
		}
		else {
			target = calcClydeTarget(pacmanPos, pacmanDir);
		}
		break;
	}
	}

	if (logClock.getElapsedTime().asSeconds() > 5.f) {
		logClock.restart();
		Log::debug(mapGhostType(ghostType) + "'s target: X: " + std::to_string(target.x) + " Y: " + std::to_string(target.y));
	}
	return target;
}

sf::Vector2i Ghost::getCurPos() {
	return map.posToGrid(ghost.getPosition());
}