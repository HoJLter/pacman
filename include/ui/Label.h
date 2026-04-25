#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/AssetsManager.h"

class Label{
private:
	sf::Text content;
	sf::Vector2f coords;
	sf::Font font;

	bool isVisible;

public:
	Label(std::string str, 
		sf::Vector2f coords, 
		uint16_t charSize, 
		sf::Color color, 
		AssetsManager& assetsManager);
	void setString(const std::string& str);

	void switchVisibility();

	void render(sf::RenderWindow& window);
};
