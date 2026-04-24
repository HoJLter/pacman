#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
#include "ui/UI.h"

class Button: public UI {
private:
	sf::RectangleShape shape;
	sf::Text label;
	sf::Font font;
	std::function<void()> callback;

	bool isPressed;

public:
	Button(sf::Vector2f padding, sf::Vector2f coords, std::string text, std::function<void()> callback);
	void update(sf::RenderWindow& window) override;
	void handleEvent(const sf::Event& event) override;
	void render(sf::RenderWindow& window) override;
};