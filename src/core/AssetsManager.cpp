#include "core/AssetsManager.h"
#include "utils/Log.h"


void AssetsManager::addFont(std::string name, std::string path) {
	sf::Font font;
	if (!font.loadFromFile(path)) {
		Log::error("Error loading font from file. Font name: " + name);
	}
	else {
		Log::debug("Font loaded: " + name);
	}
	fonts[name] = font;
}

void AssetsManager::addTexture(std::string name, std::string path) {
	sf::Texture texture;
	if (!texture.loadFromFile(path)) {
		Log::error("Error loading texture from file. Texture name: " + name);
	}
	else {
		Log::debug("Texture loaded: " + name);
	}
	textures[name] = texture;
}

AssetsManager::AssetsManager() {
	addFont("pixel", "fonts/pixel-font.otf");

	addTexture("bonuses", "bunuses.png");
	addTexture("borderExt", "borderExt.png");
	addTexture("mazeExt", "mazeExt.png");
	addTexture("mazeInt", "mazeInt.png");
	addTexture("ghosts", "ghosts.png");
	addTexture("pacmanMove", "pacmanMove.png");
	addTexture("pacmanDie", "pacmanDie.png");
}

const sf::Font& AssetsManager::getFont(const std::string& fontName) {
	if (!fonts.count(fontName)) {
		Log::error("Font get error. Unknown font");
	}
	return fonts.at(fontName);
}

const sf::Font& AssetsManager::getTexture(const std::string& textureName) {
	if (!textures.count(textureName)) {
		Log::error("Texture get error. Unknown texture");
	}
	return fonts.at(textureName);
}