#include "ui/Label.h"
#include "utils/Log.h"


Label::Label(std::string str, sf::Vector2f coords, uint16_t charSize, sf::Color color, AssetsManager& assets) {
	font = assets.getFont("pixel");
	isVisible = true;

	content.setFont(font);
	content.setString(str);
	content.setColor(color);
	content.setCharacterSize(charSize);
	sf::FloatRect bounds = content.getGlobalBounds();

	content.setOrigin({bounds.width/2, bounds.height/2});

	content.setPosition(coords);

	Log::debug("Label \"" + str + "\" was created");
}

void Label::setString(const std::string& str){
	content.setString(str);
}

void Label::switchVisibility() {
	isVisible = !isVisible;
}


void Label::render(sf::RenderWindow& window) {
	if (isVisible) {
		window.draw(content);
	}
}
