#include "core/GameEngine.h"


GameEngine::GameEngine(int w, int h) :
	window(sf::VideoMode(sf::VideoMode(w, h)), "PACMAN GAME")
{
}


void GameEngine::handleEvent() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}
void GameEngine::update() {

}
void GameEngine::render() {
	window.clear();

	window.display();
}

void GameEngine::run() {
	while (window.isOpen()) {
		handleEvent();
		update();
		render();
	}
}