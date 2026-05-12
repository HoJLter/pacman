#include "entities/Ghost.h"
#include "utils/Log.h"
#include "engine/core/Algorithms.h"


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


sf::Vector2u Ghost::calcInkyTarget(sf::Vector2u pacmanPos, sf::Vector2u blinkyPos, MoveDirection pacmanDir) {
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
		static_cast<unsigned>(finalY) };
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