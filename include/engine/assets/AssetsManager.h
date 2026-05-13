#pragma once
#include <map>
#include <string>
#include <list>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum tile {
	Money,
	Wall,
	Border,
	Teleport,
	Void,
	BlinkySpawn,
	PinkySpawn,
	InkySpawn,
	ClydeSpawn,
	PacmanSpawn,
	Gates,
	Enegrizer
};

class AssetsManager {
private:
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> sounds;
	std::vector<std::vector<int>> tilemap;

	std::list<sf::Sound> activeSounds;
	std::unordered_map<std::string, sf::Sound> loopedSounds;

	void addFont(std::string name, std::string path);
	void addTexture(std::string name, std::string path);
	void addSound(std::string name, std::string path);

	void calcTilemap();
public:
	AssetsManager();

	const sf::Font& getFont(const std::string& font);
	const sf::Texture& getTexture(const std::string& texture);

	void playSound(const std::string& sound);
	void playLoopedSound(const std::string& soundName);
	void stopLoopedSound(const std::string& soundName);
	void cleanupSounds();

	std::vector<std::vector<int>>& getTilemap();
	void logTilemap();

};
