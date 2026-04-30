#include "entities/Ghost.h"
#include "utils/Log.h"


Ghost::Ghost(GameContext& context, GhostType type, float scale):
	context(context),
	type(type),
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
	Log::debug(mapGhostType(type) + " has been created");
	ghost.setTexture(ghostMoveTexture);
	ghost.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
	ghost.setPosition({ context.settings.viewWidth / 2.f, context.settings.viewHeight / 2.f });
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