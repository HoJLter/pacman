#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/Animation.h"
#include "engine/GameContext.h"
#include "entities/EntityData.h"
#include "entities/IMap.h"


class Ghost {
private:
	
	enum class Mode{
		Scatter,
		Chase
	};

	GameContext& context;
	IMap& map;
	GhostType ghostType;

	int Ghost::chooseAnimRow();
	sf::Sprite ghost;
	sf::Texture ghostMoveTexture;
	Animation ghostMoveAnimation;
	sf::Clock animationClock;

	float speedPerSec;
	float scale;

	Mode curMode;
	sf::Clock modeClock;

	sf::Clock logClock;

	sf::Vector2i updateTarget(sf::Vector2i pacmanPos, sf::Vector2i blinkyPos, MoveDirection pacmanDir);
	sf::Vector2i calcBlinkyTarget(sf::Vector2i pacmanPos, MoveDirection pacmanDir);
	sf::Vector2i calcPinkyTarget(sf::Vector2i pacmanPos, MoveDirection pacmanDir);
	sf::Vector2i calcInkyTarget(sf::Vector2i pacmanPos, sf::Vector2i blinkyPos, MoveDirection pacmanDir);
	sf::Vector2i calcClydeTarget(sf::Vector2i pacmanPos, MoveDirection pacmanDir);

	sf::Clock sleepClock;
	bool isSleeping;
	void wakeUp();

	MoveDirection curDirection;
	MoveDirection chooseNextDirection(sf::Vector2i target, const std::vector<MoveDirection>& possibleDirs);
	std::vector<MoveDirection> calcPossibleDirs();
	void move(float dt);
public:
	Ghost::Ghost(GameContext& context, IMap& map, GhostType type, sf::Vector2i initPos, float scale);

	sf::Vector2i getCurPos();

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, sf::Vector2i pacmanPos, MoveDirection pacmanDir, sf::Vector2i blinkyPos, float dt);
	void render(sf::RenderWindow& window);
};

