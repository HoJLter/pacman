#include "engine/assets/Animation.h"
#include "utils/Log.h"

Animation::Animation(sf::Texture& texture,
	int frames,
	int frameWidth,
	int frameHeight,
	int rowY,
	float speed):
	texture(texture),
	frames(frames),
	frameWidth(frameWidth),
	frameHeight(frameHeight),
	rowY(rowY),
	speed(speed)
{};

void Animation::update(float dt) {
	timer += dt;
	if (timer > speed) {
		timer = 0;
		currentFrame = (currentFrame + 1) % frames;
	}
}

void Animation::applyToSprite(sf::Sprite& sprite) {
	sprite.setTextureRect(sf::IntRect(
		{ currentFrame * frameWidth, rowY * frameHeight},
		{frameWidth, frameHeight}));
}

void Animation::changeRow(int row) {
	rowY = row;
}