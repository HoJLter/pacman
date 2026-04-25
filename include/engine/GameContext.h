#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/AssetsManager.h"
#include "engine/core/GameSettings.h"

struct GameContext {
	sf::RenderWindow& window;
	AssetsManager& assetsManager;
	GameSettings& settings;
};