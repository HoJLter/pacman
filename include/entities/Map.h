#pragma once
#include "engine/assets/AssetsManager.h"
#include "entities/IMap.h"
#include "engine/GameContext.h"
#include "utils/Log.h"
#include <vector>

class Map: public IMap {
private:
	GameContext& context;
	float scale;
	int TS;
	
	sf::Vector2f mapOffset;

	std::vector<std::vector<sf::Sprite>> sprites;
	std::vector<std::vector<int>>& tilemap;
	sf::Vector2u tilemapSize;

	sf::IntRect calcWallType(int x, int y, tile tiletype);
	sf::Vector2f calcOffset();
public:
	Map(GameContext& context, float scale);

	sf::Vector2u getSize() override { return tilemapSize; };
	sf::Vector2u posToGrid(sf::Vector2f pos) override;
	sf::Vector2f gridToPos(sf::Vector2u gridPos) override;

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};