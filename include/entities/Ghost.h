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
	GhostType ghostType;

	sf::Sprite ghost;
	sf::Texture ghostMoveTexture;
	MoveDirection curDirection;
	Animation ghostMove;
	sf::Clock animationClock;

	float speedPerSec;
	float scale;
	bool isFreezed;
	sf::Clock freezeClock;
	sf::Clock logClock;

	sf::Vector2u calcTarget(sf::Vector2u pacmanPos, sf::Vector2u blinkyPos, MoveDirection pacmanDir);
	sf::Vector2u calcBlinkyTarget(sf::Vector2u pacmanPos, MoveDirection pacmanDir);
	sf::Vector2u calcPinkyTarget(sf::Vector2u pacmanPos, MoveDirection pacmanDir);
	sf::Vector2u calcInkyTarget(sf::Vector2u pacmanPos, sf::Vector2u blinkyPos, MoveDirection pacmanDir);
	sf::Vector2u calcClydeTarget(sf::Vector2u pacmanPos, MoveDirection pacmanDir);

public:
	Ghost::Ghost(GameContext& context, IMap& map, GhostType type, sf::Vector2u initPos, float scale);

	sf::Vector2u getCurPos();

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, sf::Vector2u pacmanPos, MoveDirection pacmanDir, sf::Vector2u blinkyPos, float dt);
	void render(sf::RenderWindow& window);
};

