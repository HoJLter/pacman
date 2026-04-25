#pragma once
#include "SFML/Graphics.hpp"
#include "engine/scene/SceneManager.h"
#include "engine/assets/AssetsManager.h"
#include "engine/core/GameSettings.h"



class GameEngine {
private:
	sf::RenderWindow window;
	sf::View view;

	GameSettings settings;
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