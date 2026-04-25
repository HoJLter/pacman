#include "engine/core/GameEngine.h"
#include "utils/Log.h"


GameEngine::GameEngine(int w, int h) :
	window(sf::VideoMode(sf::VideoMode(w, h)), "PACMAN GAME"),
	settings{1920.f, 1080.f},
	assetsManager(),
	context{ window, assetsManager, settings },
	sceneManager(context)
{
	view = sf::View(sf::FloatRect(0.f, 0.f, settings.viewWidth, settings.viewHeight));
	applyLetterbox();
	Log::debug("GameEngine was created");
}


void GameEngine::handleEvent() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

        if (event.type == sf::Event::Resized) {
			applyLetterbox();
        }
		sceneManager.handleEvent(event);
	}
}
void GameEngine::update() {
	assetsManager.cleanupSounds();
	sceneManager.update();

}
void GameEngine::render() {
	window.clear(sf::Color::Black);
	

	sf::RectangleShape bg({ settings.viewWidth, settings.viewHeight});
	bg.setFillColor(sf::Color(50, 50, 50));
	bg.setPosition(0, 0);
	window.draw(bg);

	sceneManager.render();
	
	window.display();
}

void GameEngine::run() {
	while (window.isOpen()) {
		handleEvent();
		update();
		render();
	}
}


void GameEngine::applyLetterbox() {
	float windowWidth = window.getSize().x;
	float windowHeight = window.getSize().y;

	float gameRatio = settings.viewWidth / settings.viewHeight;
	float windowRatio = windowWidth / windowHeight;

	float viewportX = 0.f;
	float viewportY = 0.f;
	float viewportWidth = 1.f;
	float viewportHeight = 1.f;

	if (windowRatio > gameRatio) {
		// окно шире тогда режем ширину
		float realWidth = windowHeight * gameRatio;
		viewportWidth = realWidth / windowWidth;
		viewportX = (1.f - viewportWidth) / 2.f;
	}
	else {
		// окно выше тогда режем высоту
		float realHeight = windowWidth / gameRatio;
		viewportHeight = realHeight / windowHeight;
		viewportY = (1.f - viewportHeight) / 2.f;
	}

	view.setViewport(sf::FloatRect(
		viewportX,
		viewportY,
		viewportWidth,
		viewportHeight
	));

	window.setView(view);
}