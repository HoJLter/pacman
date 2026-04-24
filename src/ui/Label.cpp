#include "ui/Label.h"
#include "utils/Log.h"


Label::Label(std::string str, sf::Vector2f coords, uint16_t charSize) {
	if (!font.loadFromFile("assets/pixel-font.otf")) {
		Log::error("Font loading was failed");
		throw std::runtime_error("Font loading was failed");
	}
	isVisible = true;

	content.setFont(font);
	content.setString(str);
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
