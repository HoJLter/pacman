#include <iostream>
#include <functional>
#include "ui/Button.h"
#include "utils/Log.h"

Button::Button(sf::Vector2f padding, sf::Vector2f coords, std::string text, std::function<void()> callback) {
	this->callback = callback;
	
	//LABEL
	isPressed = false;

	label.setString(text);
	if (!font.loadFromFile("assets/pixel-font.otf")) {
		Log::error("Font loading was failed");
		throw std::runtime_error("Font loading was failed");
	}
	label.setFont(font);
	label.setColor(sf::Color::Red);
	sf::FloatRect labelBounds = label.getGlobalBounds();
	label.setOrigin({labelBounds.width/2, labelBounds.height/2});
	label.setPosition(coords);

	//SHAPE
	shape.setSize({ labelBounds.width + (padding.x * 2), labelBounds.height + (padding.y*2)});
	sf::FloatRect shapeBounds = shape.getGlobalBounds();
	shape.setOrigin({ shapeBounds.width / 2, shapeBounds.height / 2 });
	shape.setPosition(coords);

	Log::debug("Button \"" + text + "\" was created");
}

void Button::update(sf::RenderWindow& window) {
	sf::Vector2i curPosInt = sf::Mouse::getPosition(window);
	sf::Vector2f curPosFloat(
		static_cast<float>(curPosInt.x),
		static_cast<float>(curPosInt.y)
	);
	bool isHovered = shape.getGlobalBounds().contains(curPosFloat);
	sf::Vector2f scale = shape.getScale();
	if (isHovered) {
		shape.setFillColor(sf::Color::Cyan);
	}
	else {
		shape.setFillColor(sf::Color::White);
	}

	if (isPressed) {
		shape.setScale({ 0.9f, 0.9f });
		label.setScale({ 0.9f, 0.9f });
	}
	else {
		shape.setScale({ 1.f, 1.f });
		label.setScale({ 1.f, 1.f });
	};
}

void Button::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f mousePos = { 
			static_cast<float>(event.mouseButton.x), 
			static_cast<float>(event.mouseButton.y) 
		};
		if (shape.getGlobalBounds().contains(mousePos)) {
			Log::debug("Mouse click coords: " +
				std::to_string(event.mouseButton.x) + " " +
				std::to_string(event.mouseButton.y) +
				" Button coords: " +
				std::to_string((int)shape.getGlobalBounds().left) + " " +
				std::to_string((int)shape.getGlobalBounds().top));
			Log::debug("Button \"" + label.getString() + "\" is pressesd");

			sf::Clock clock;
			isPressed = true;
			
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f mousePos = {
			static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y)
		};
		if (shape.getGlobalBounds().contains(mousePos)) {
			callback();
			isPressed = false;
		}
	}
}

void Button::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(label);
}