#include "entities/Ghost.h"
#include "utils/Log.h"
#include "engine/core/Algorithms.h"
#include <algorithm>
#include <cmath>


Ghost::Ghost(GameContext& context, IMap& map, GhostType type, sf::Vector2i initPos, float scale):
	context(context),
	map(map),
	ghostType(type),
	scale(scale),
	speedPerSec(250.f),
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
	curMode = Mode::Scatter;
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
	sf::Vector2i pacmanPos, 
	MoveDirection pacmanDir, 
	sf::Vector2i blinkyPos, 
	float dt) 
{
	if (isSleeping) {
		wakeUp();
	}
	if (curMode == Mode::Scatter &&
		modeClock.getElapsedTime().asSeconds() > 7.f) {
		modeClock.restart();
		curMode = Mode::Chase;
		Log::debug("CurMode = Chase");
	}
	else if (curMode == Mode::Chase &&
		modeClock.getElapsedTime().asSeconds() > 20.f) {
		modeClock.restart();
		curMode = Mode::Scatter;
		Log::debug("CurMode = Scatter");
	}

	sf::Vector2i target = updateTarget(pacmanPos, blinkyPos, pacmanDir);
	int freeDirs= getFreeDirsCount();
	if (map.isOnCenter(ghost.getPosition())) {
		MoveDirection nextDirection = chooseNextDirection(target);
		if ((freeDirs == 2 &&
			nextDirection != curDirection) ||
			freeDirs >= 3 ||
			freeDirs == 1)
		{
			curDirection = nextDirection;
		}
	}

	if (!isSleeping) {
		move(dt);
	}

	ghostMoveAnimation.update(dt);
	ghostMoveAnimation.applyToSprite(ghost);
}


void Ghost::render(sf::RenderWindow& window) {
	window.draw(ghost);
}


void Ghost::wakeUp() {
	switch (ghostType) {
		case GhostType::Blinky: {
			isSleeping = false;
			break;
		}
		case GhostType::Pinky: {
			if (sleepClock.getElapsedTime().asSeconds() > 5.f) {
				isSleeping = false;
			}
			break;
		}
		case GhostType::Inky: {
			if (sleepClock.getElapsedTime().asSeconds() > 10.f) {
				isSleeping = false;
			}
			break;
		}
		case GhostType::Clyde: {
			if (sleepClock.getElapsedTime().asSeconds() > 20.f) {
				isSleeping = false;
			}
			break;
		}
	}
}

void Ghost::move(float dt) {
	sf::Vector2i moveVector = dirToVector(curDirection);
	ghost.move({
		(moveVector.x) * (speedPerSec * dt),
		(moveVector.y) * (speedPerSec * dt)
	});
}

int Ghost::getFreeDirsCount() {
	sf::Vector2i curPosition = map.posToGrid(ghost.getPosition());
	std::vector<MoveDirection> dirs = {
		MoveDirection::Up, MoveDirection::Left,
		MoveDirection::Down, MoveDirection::Right
	};
	int result = 0;
	for (auto dir : dirs) {
		result += map.isFreeDirection(curPosition, dir);
	}
	// Log::debug(std::to_string(result > 2) + mapGhostType(ghostType));
	return result;
}

MoveDirection Ghost::chooseNextDirection(sf::Vector2i target) {
	sf::Vector2i curPosition = map.posToGrid(ghost.getPosition());
	
	std::vector<MoveDirection> dirs = { 
		MoveDirection::Up, MoveDirection::Left,
		MoveDirection::Down, MoveDirection::Right 
	};
	
	float minDistance = 10000.f;
	MoveDirection bestDirection = MoveDirection::None;

	for (auto dir : dirs) {
		sf::Vector2i dirVector = dirToVector(dir);
		sf::Vector2i nextTile = {
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
	return bestDirection;
}

