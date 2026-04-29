#pragma once
#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum tile {
	Money,
	Wall,
	Border,
	Teleport,
	BlinkySpawn,
	PinkySpawn,
	InkySpawn,
	ClydeSpawn,
	PacmanSpawn
};

class AssetsManager {
private:
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> sounds;
	std::vector<std::vector<int>> tilemap;

	std::vector<sf::Sound> activeSounds;

	void addFont(std::string name, std::string path);
	void addTexture(std::string name, std::string path);
	void addSound(std::string name, std::string path);

	void calcTilemap();
public:
	AssetsManager();

	const sf::Font& getFont(const std::string& font);
	const sf::Texture& getTexture(const std::string& texture);

	void playSound(const std::string& sound);
	void AssetsManager::cleanupSounds();

	std::vector<std::vector<int>>& getTilemap();
	void logTilemap();

};