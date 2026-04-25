#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/AssetsManager.h"
#include "engine/core/GameSettings.h"
#include "engine/scene/ISceneSwitcher.h"

struct GameContext {
	sf::RenderWindow& window;
	AssetsManager& assetsManager;
	ISceneSwitcher& sceneSwitcher;
	GameSettings& settings;
};