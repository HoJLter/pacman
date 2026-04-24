#pragma once
#include "SFML/Graphics.hpp"
#include "SceneManager.h"


class GameEngine {
private:
	sf::RenderWindow window;
	sf::View view;

	SceneManager sceneManager;

	void GameEngine::applyLetterbox();

	void render();
	void update();
	void handleEvent();
public:
	GameEngine(int width, int height);
	void run();
};