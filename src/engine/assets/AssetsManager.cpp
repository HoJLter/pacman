#include "engine/assets/AssetsManager.h"
#include "utils/Log.h"
#include <sstream>
#include <iomanip>



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

	//addTexture("bonuses", "assets/game/maze/bonuses.png");
	addTexture("gates", "assets/game/maze/gates.png");
	addTexture("fear", "assets/game/ghosts/fear.png");
	addTexture("energizer", "assets/game/energizer.png");

	addTexture("border", "assets/game/maze/border.png");
	addTexture("void", "assets/game/maze/void.png");
	addTexture("maze", "assets/game/maze/maze.png");
	addTexture("money", "assets/game/money.png");
	addTexture("blinky", "assets/game/ghosts/blinky.png");
	addTexture("pinky", "assets/game/ghosts/pinky.png");
	addTexture("inky", "assets/game/ghosts/inky.png");
	addTexture("clyde", "assets/game/ghosts/clyde.png");
	addTexture("pacmanMove", "assets/game/pacmanMove.png");
	addTexture("pacmanDie", "assets/game/pacmanDie.png");
	addTexture("icon", "assets/game/icon.png");
	addTexture("tilemap", "assets/game/tileMap2.png");
	addSound("start", "assets/sounds/startSound.mp3");
	addSound("pickup", "assets/sounds/pickup.mp3");


	calcTilemap();
	logTilemap();
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
	if (!sounds.count(soundName)) {
		Log::error("Sound get error. Unknown sound");
		return;
	}
	activeSounds.emplace_back();
	activeSounds.back().setBuffer(sounds[soundName]);
	activeSounds.back().setVolume(20.f);
	activeSounds.back().play();

	Log::debug("Sound " + soundName + " is played");
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


void AssetsManager::logTilemap() {
	for (const auto& row : tilemap) {
		std::stringstream ss;

		for (int val : row) {
			ss << std::setw(2) << val;
		}

		Log::debug(ss.str());
	}
}

void AssetsManager::calcTilemap() {
	Log::debug("Tilemap calculation has been started");

	sf::Texture tilemapTexture = getTexture("tilemap");
	sf::Image tilemapImage = tilemapTexture.copyToImage();

	int mapWidth = tilemapImage.getSize().x;
	int mapHeight = tilemapImage.getSize().y;

	tilemap.resize(mapHeight, std::vector<int>(mapWidth, 0));

	sf::Color moneyColor = sf::Color(223, 113, 38);
	sf::Color borderColor = sf::Color(240, 33, 52);
	sf::Color wallColor = sf::Color(33, 33, 240);
	sf::Color gatesColor = sf::Color(251, 242, 54);

	sf::Color teleportColor = sf::Color(33, 240, 64);

	sf::Color blinkySpawnColor = sf::Color(165, 0, 0);
	sf::Color pinkySpawnColor = sf::Color(240, 33, 255);
	sf::Color inkySpawnColor = sf::Color(33, 211, 255);
	sf::Color clydeSpawnColor = sf::Color(255, 122, 33);

	sf::Color pacmanSpawnColor = sf::Color(255, 204, 0);
	sf::Color energizerColor = sf::Color(255, 192, 33);

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			sf::Color pixelColor = tilemapImage.getPixel(x, y);

			if (pixelColor == moneyColor) {
				tilemap[y][x] = tile::Money;
			}
			else if (pixelColor == borderColor) {
				tilemap[y][x] = tile::Border;
			}
			else if (pixelColor == wallColor) {
				tilemap[y][x] = tile::Wall;
			}
			else if (pixelColor == teleportColor) {
				tilemap[y][x] = tile::Teleport;
			}
			else if (pixelColor == blinkySpawnColor) {
				tilemap[y][x] = tile::BlinkySpawn;
			}
			else if (pixelColor == pinkySpawnColor) {
				tilemap[y][x] = tile::PinkySpawn;
			}
			else if (pixelColor == inkySpawnColor) {
				tilemap[y][x] = tile::InkySpawn;
			}
			else if (pixelColor == clydeSpawnColor) {
				tilemap[y][x] = tile::ClydeSpawn;
			}
			else if (pixelColor == pacmanSpawnColor) {
				tilemap[y][x] = tile::PacmanSpawn;
			}
			else if (pixelColor == gatesColor) {
				tilemap[y][x] = tile::Gates;
			}
			else if (pixelColor == energizerColor) {
				tilemap[y][x] = tile::Enegrizer;
			}
			else {
				tilemap[y][x] = tile::Void;
			}
		}
	}

	Log::debug("Tilemap calculation has been ended");
}

std::vector<std::vector<int>>& AssetsManager::getTilemap() {
	return tilemap;
}