#include "engine/assets/AssetsManager.h"
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

void AssetsManager::addSound(std::string name, std::string path) {
	sf::SoundBuffer soundBuffer;
	if (!soundBuffer.loadFromFile(path)) {
		Log::error("Error loading sound from file. Font name: " + name);
	}
	else {
		Log::debug("Sound loaded: " + name);
		sounds[name] = soundBuffer;
	}
}


AssetsManager::AssetsManager() {
	addFont("pixel", "assets/fonts/pixel-font.otf");

	addTexture("bonuses", "assets/game/bonuses.png");
	addTexture("borderExt", "assets/game/borderExt.png");
	addTexture("mazeExt", "assets/game/mazeExt.png");
	addTexture("mazeInt", "assets/game/mazeInt.png");
	addTexture("ghosts", "assets/game/ghosts.png");
	addTexture("pacmanMove", "assets/game/pacmanMove.png");
	addTexture("pacmanDie", "assets/game/pacmanDie.png");

	addSound("start", "assets/sounds/startSound.mp3");
}

const sf::Font& AssetsManager::getFont(const std::string& fontName) {
	if (!fonts.count(fontName)) {
		Log::error("Font get error. Unknown font");
	}
	return fonts.at(fontName);
}

const sf::Texture& AssetsManager::getTexture(const std::string& textureName) {
	if (!textures.count(textureName)) {
		Log::error("Texture get error. Unknown texture");
	}
	return textures.at(textureName);
}

void AssetsManager::playSound(const std::string& soundName) {
	sf::Sound sound;
	if (!sounds.count(soundName)) {
		Log::error("Sound get error. Unknown sound");
		return;
	}
	sound.setBuffer(sounds[soundName]);
	Log::debug("Sound " + soundName + " is played");
	activeSounds.push_back(sound);
	activeSounds.back().play();
}

void AssetsManager::cleanupSounds() {
	for (auto it = activeSounds.begin(); it != activeSounds.end(); ) {
		if (it->getStatus() == sf::Sound::Stopped) {
			it = activeSounds.erase(it);
		}
		else {
			++it;
		}
	}
}