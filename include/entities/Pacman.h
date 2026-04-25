#pragma once
#include "SFML/Graphics.hpp"

class Pacman {
private:
	sf::Texture pacmanTexture;
	sf::CircleShape pacman;

public:
	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};