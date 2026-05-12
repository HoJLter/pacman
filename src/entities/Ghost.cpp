#include "entities/Ghost.h"
#include "utils/Log.h"
#include "engine/core/Algorithms.h"
#include <algorithm>
#include <cmath>


Ghost::Ghost(GameContext& context, IMap& map, GhostType type, sf::Vector2u initPos, float scale):
	context(context),
	map(map),
	ghostType(type),
	scale(scale),
	speedPerSec(10.f),
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
	//Log::debug(mapGhostType(type) + " has been created. X: " + std::to_string(initPos.x) + " Y: " + std::to_string(initPos.y));
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

	if (isOnCross() && isOnCenter()) {
		curDirection = chooseNextDirection(target);
	}
	move(dt);

	ghostMoveAnimation.update(dt);
	ghostMoveAnimation.applyToSprite(ghost);
}


void Ghost::render(sf::RenderWindow& window) {
	window.draw(ghost);
}

void Ghost::move(float dt) {
	sf::Vector2i moveVector = dirToVector(curDirection);
	ghost.move({
		(moveVector.x) * (speedPerSec * dt),
		(moveVector.y) * (speedPerSec * dt)
	});
}

bool Ghost::isOnCenter() {
	sf::Vector2f curPosition = ghost.getPosition();
	sf::Vector2f tileCenter = map.gridToPos(map.posToGrid(curPosition));
	sf::Vector2f delta = { 4.f, 4.f };
	
	sf::Vector2f distance = curPosition - tileCenter;
	Log::debug(std::to_string(std::abs(distance.x) <= delta.x &&
		std::abs(distance.y) <= delta.y) + mapGhostType(ghostType));

	return 
		std::abs(distance.x) <= delta.x &&
		std::abs(distance.y) <= delta.y;
}

bool Ghost::isOnCross() {
	sf::Vector2u curPosition = map.posToGrid(ghost.getPosition());
	std::vector<MoveDirection> dirs = {
		MoveDirection::Up, MoveDirection::Left,
		MoveDirection::Down, MoveDirection::Right
	};
	int result = 0;
	for (auto dir : dirs) {
		result += map.isFreeDirection(curPosition, dir);
	}
	// Log::debug(std::to_string(result > 2) + mapGhostType(ghostType));
	return result > 2;
}

MoveDirection Ghost::chooseNextDirection(sf::Vector2u target) {
	sf::Vector2u curPosition = map.posToGrid(ghost.getPosition());
	
	std::vector<MoveDirection> dirs = { 
		MoveDirection::Up, MoveDirection::Left,
		MoveDirection::Down, MoveDirection::Right 
	};
	
	float minDistance = 10000.f;
	MoveDirection bestDirection = MoveDirection::None;

	for (auto dir : dirs) {
		sf::Vector2i dirVector = dirToVector(dir);
		sf::Vector2u nextTile = {
			curPosition.x + dirVector.x,
			curPosition.y + dirVector.y
		};

		if (!map.isFree(nextTile))
			continue;

		float distance = calcDistance(nextTile, target);
		if (distance < minDistance) {
			minDistance = distance;
			bestDirection = dir;
		}
	}
	Log::debug(mapGhostType(ghostType) + ": " + mapDirection(curDirection));
	return bestDirection;
}

