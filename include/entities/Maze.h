#pragma once
#include "engine/assets/AssetsManager.h"
#include "engine/GameContext.h"
#include "utils/Log.h"
#include <vector>

class Maze {
private:
	std::vector<std::vector<sf::Sprite>> sprites;
	std::vector<std::vector<int>>& tilemap;
	float scale;
	sf::IntRect calculateTile(int x, int y, tile tiletype);
public:
	Maze(GameContext& context, float scale);
	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};