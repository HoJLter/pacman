#pragma once
#include "SFML/Graphics.hpp"

class Animation {
private:
	sf::Texture& texture;
	int frames;
	int frameWidth;
	int frameHeight;
	int rowY;
	float speed;

	float timer = 0;
	int currentFrame = 0;
public:
	Animation(sf::Texture& texture,
		int frames,
		int frameWidth,
		int frameHeight,
		int rowY,
		float speed);
	
	void update(float dt);
	
	void changeRow(int row);
	void applyToSprite(sf::Sprite& sprite);
};