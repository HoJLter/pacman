#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/AssetsManager.h"
#include "engine/core/GameSettings.h"
#include <queue>


enum class EventType {
	CoinCollected
};

struct GameEvent {
	EventType type;
	sf::Vector2u tilePos;
};

struct GameContext {
	sf::RenderWindow& window;
	AssetsManager& assetsManager;
	GameSettings& settings;

	std::queue<GameEvent> eventQueue;
};