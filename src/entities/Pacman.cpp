#include "entities/Pacman.h"
#include "utils/Log.h"


Pacman::Pacman(GameContext& context) :
	context(context),
	speedPerSec(200.f),
	pacmanMoveTexture(context.assetsManager.getTexture("pacmanMove")),
	pacmanMove(
		pacmanMoveTexture, // texture
		2,                 // frames
		16,                // frameWidth
		16,                // frameHeight
		0,                 // row
		0.2f			   // animation speed (in seconds)
	)
{
	Log::debug("Pacman has been created");
	pacman.setTexture(pacmanMoveTexture);
	pacman.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
	pacman.setPosition({context.settings.viewWidth/2.f, context.settings.viewHeight/2.f});
	pacman.setScale({ 10.f, 10.f });
}

void Pacman::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			case sf::Keyboard::Up: {
				pacmanMove.changeRow(2);
				curDirection = MoveDirection::Up;
				break;
			}
			case sf::Keyboard::Down: {
				pacmanMove.changeRow(3);
				curDirection = MoveDirection::Down;
				break;
			}
			case sf::Keyboard::Left: {
				pacmanMove.changeRow(1);
				curDirection = MoveDirection::Left;
				break;
			}
			case sf::Keyboard::Right: {
				pacmanMove.changeRow(0);
				curDirection = MoveDirection::Right;
				break;
			}
		}
	}
}
void Pacman::update(sf::RenderWindow& window, float dt) {
	switch (curDirection) {
		case MoveDirection::Up: {
			pacman.move({ 0.f, -speedPerSec*dt });
			break;
		}
		case MoveDirection::Down: {
			pacman.move({ 0.f, +speedPerSec*dt });
			break;
		}
		case MoveDirection::Left: {
			pacman.move({ -speedPerSec*dt, 0.f });
			break;
		}
		case MoveDirection::Right: {
			pacman.move({ +speedPerSec * dt, 0.f });
			break;
		}

	}
	pacmanMove.update(dt);
	pacmanMove.applyToSprite(pacman);
}
void Pacman::render(sf::RenderWindow& window) {
	window.draw(pacman);
}