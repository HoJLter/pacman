#include "scenes/MenuScene.h"


MenuScene::MenuScene(sf::Vector2u windowSize, ISceneSwitcher& ss):
	Scene(ss),
	startButton(
		{20.f, 20.f},
		{300.f, 300.f},
		"LET'S GO!",
		[this]() {
			this->sceneSwitcher.requestSwitchScene(SceneID::Game);
		})
{

}


void MenuScene::handleEvent(const sf::Event& event, sf::RenderWindow& window){
	startButton.handleEvent(event, window);
}


void MenuScene::update(sf::RenderWindow& window) {
	startButton.update(window);

}


void MenuScene::render(sf::RenderWindow& window) {
	startButton.render(window);
}