#pragma once
#include <map>
#include <string>
#include "SFML/Graphics.hpp"


class AssetsManager {
private:
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::Texture> textures;

	void addFont(std::string name, std::string path);
	void addTexture(std::string name, std::string path);
public:
	AssetsManager();

	const sf::Font& getFont(const std::string& font);
	const sf::Font& getTexture(const std::string& font);
};