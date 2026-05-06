#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/Animation.h"
#include "engine/GameContext.h"
#include "entities/EntityData.h"
#include "entities/IMap.h"


class Ghost {
private:
	GameContext& context;
	IMap& map;
	GhostType type;

	sf::Sprite ghost;
	sf::Texture ghostMoveTexture;
	MoveDirection curDirection;
	Animation ghostMove;
	sf::Clock animationClock;

	float speedPerSec;
	float scale;
public:
	Ghost::Ghost(GameContext& context, IMap& map, GhostType type, sf::Vector2u initPos, float scale);

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};

