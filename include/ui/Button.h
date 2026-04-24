#pragma once
#include "SFML/Graphics.hpp"
#include <functional>

class Button {
private:
	sf::RectangleShape shape;
	sf::Text label;
	sf::Font font;
	std::function<void()> callback;

	bool isPressed;

public:
	Button(sf::Vector2f padding, sf::Vector2f coords, std::string text, std::function<void()> callback);
	void update(sf::RenderWindow& window);
	void handleEvent(const sf::Event& event, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};