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
	std::vector<MoveDirection> possibleDirs = calcPossibleDirs();

	if (map.isOnCenter(ghost.getPosition())) {
		if (possibleDirs.empty()) {
			curDirection = calcReverseDir(curDirection);
		}
		else if (possibleDirs.size() == 1) {
			curDirection = possibleDirs[0];
		}
		else {
			curDirection = chooseNextDirection(target, possibleDirs);
		}
	}

	if (!isSleeping) {
		move(dt);
	}

	ghostMoveAnimation.changeRow(chooseAnimRow());
	ghostMoveAnimation.update(dt);
	ghostMoveAnimation.applyToSprite(ghost);
}

int Ghost::chooseAnimRow() {
	switch (curDirection) {
	case MoveDirection::Up:   return 2;
	case MoveDirection::Down: return 3;
	case MoveDirection::Left: return 1;
	case MoveDirection::Right:return 0;
	}
	return 3;
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

std::vector<MoveDirection> Ghost::calcPossibleDirs() {
	sf::Vector2i gridPos = map.posToGrid(ghost.getPosition());

	bool canUp = map.isFreeDirection(gridPos, MoveDirection::Up);
	bool canDown = map.isFreeDirection(gridPos, MoveDirection::Down);
	bool canLeft = map.isFreeDirection(gridPos, MoveDirection::Left);
	bool canRight = map.isFreeDirection(gridPos, MoveDirection::Right);

	MoveDirection reverseDir = calcReverseDir(curDirection);

	std::vector<MoveDirection> possibleDirs;
	if (canUp && reverseDir != MoveDirection::Up)
		possibleDirs.push_back(MoveDirection::Up);

	if (canDown && reverseDir != MoveDirection::Down)
		possibleDirs.push_back(MoveDirection::Down);

	if (canLeft && reverseDir != MoveDirection::Left)
		possibleDirs.push_back(MoveDirection::Left);

	if (canRight && reverseDir != MoveDirection::Right)
		possibleDirs.push_back(MoveDirection::Right);

	return possibleDirs;
}

MoveDirection Ghost::chooseNextDirection(sf::Vector2i target, 
	const std::vector<MoveDirection>& possibleDirs) {
	sf::Vector2i curPosition = map.posToGrid(ghost.getPosition());
	
	float minDistance = 10000.f;
	MoveDirection bestDirection = MoveDirection::None;

	for (auto dir : possibleDirs) {
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

