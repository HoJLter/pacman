#pragma once
#include "SFML/Graphics.hpp"
#include "engine/scene/SceneManager.h"
#include "engine/assets/AssetsManager.h"
#include "engine/core/GameSettings.h"
#include "engine/GameContext.h"


class GameEngine {
private:
	sf::RenderWindow window;
	sf::View view;

	GameSettings settings;
	AssetsManager assetsManager;
	GameContext context;
	SceneManager sceneManager;

	void GameEngine::applyLetterbox();

	void render();
	void update();
	void handleEvent();
public:
	GameEngine(int width, int height);
	void run();
};