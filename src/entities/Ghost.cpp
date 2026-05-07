#include "entities/Ghost.h"
#include "utils/Log.h"


Ghost::Ghost(GameContext& context, IMap& map, GhostType type, sf::Vector2u initPos, float scale):
	context(context),
	map(map),
	ghostType(type),
	scale(scale),
	speedPerSec(200.f),
	ghostMoveTexture(context.assetsManager.getTexture(mapGhostType(type))),
	ghostMove(
		ghostMoveTexture, // texture
		2,                 // frames
		16,                // frameWidth
		16,                // frameHeight
		0,                 // row
		0.1f			   // animation speed (in seconds)
	)
{
	Log::debug(mapGhostType(type) + " has been created. X: " + std::to_string(initPos.x) + " Y: " + std::to_string(initPos.y));
	ghost.setOrigin(8.f, 8.f);
	ghost.setTexture(ghostMoveTexture);
	ghost.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
	ghost.setPosition(map.gridToPos(initPos));
	ghost.setScale({ scale, scale });
}

void Ghost::handleEvent(const sf::Event& event) {

}
void Ghost::update(sf::RenderWindow& window, float dt) {
	ghostMove.update(dt);
	ghostMove.applyToSprite(ghost);
}
void Ghost::render(sf::RenderWindow& window) {
	window.draw(ghost);
}


sf::Vector2u Ghost::calcBlinkyTarget() {
	sf::Vector2u target;
	return target;
}
sf::Vector2u Ghost::calcPinkyTarget() {
	sf::Vector2u target;
	return target;
}
sf::Vector2u Ghost::calcInkyTarget() {
	sf::Vector2u target;
	return target;
}
sf::Vector2u Ghost::calcClydeTarget() {
	sf::Vector2u target;
	return target;
}


sf::Vector2u Ghost::calcTarget() {
	sf::Vector2u target;
	switch (ghostType) {
		case GhostType::Blinky:{
			break;
		}
		case GhostType::Pinky: {
			break;
		}
		case GhostType::Inky: {
			break;
		}
		case GhostType::Clyde: {
			break;
		}
	}
	return target;
}

sf::Vector2u Ghost::getCurPos() {
	return map.posToGrid(ghost.getPosition());
}