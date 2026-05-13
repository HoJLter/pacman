#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/AssetsManager.h"
#include "engine/core/GameSettings.h"
#include <queue>


enum class EventType {
	CoinCollected,
	EnergizerCollected
};

struct GameEvent {
	EventType type;
	sf::Vector2i tilePos;
};

struct GameData {
	int score;
};

struct GameContext {
	sf::RenderWindow& window;
	AssetsManager& assetsManager;
	GameSettings& settings;

	std::queue<GameEvent> eventQueue;
	GameData data;
};