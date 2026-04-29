#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/Animation.h"
#include "engine/GameContext.h"
#include "entities/EntityData.h"


class Ghost {
private:
	GameContext& context;
	GhostType type;

	sf::Sprite ghost;
	sf::Texture ghostMoveTexture;
	MoveDirection curDirection;
	Animation ghostMove;
	sf::Clock animationClock;

	float speedPerSec;

public:
	Ghost::Ghost(GameContext& context, GhostType type);

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};

