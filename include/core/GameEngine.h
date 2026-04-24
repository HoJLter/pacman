#pragma once
#include "SFML/Graphics.hpp"
#include "core/SceneManager.h"
#include "core/AssetsManager.h"


class GameEngine {
private:
	sf::RenderWindow window;
	sf::View view;

	SceneManager sceneManager;
	AssetsManager assetsManager;

	void GameEngine::applyLetterbox();

	void render();
	void update();
	void handleEvent();
public:
	GameEngine(int width, int height);
	void run();
};