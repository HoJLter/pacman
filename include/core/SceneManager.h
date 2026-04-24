#pragma once
#include <iostream>
#include "Scenes.h"
#include "core/ISceneSwitcher.h"
#include <memory>
#include <optional>

std::string sceneIdToStr(SceneID id);

class SceneManager: public ISceneSwitcher {
private:
	sf::RenderWindow& window;
	std::unique_ptr<Scene> curScene;
	std::optional<SceneID> requestedScene;
public:
	SceneManager(sf::RenderWindow& window);

	void requestSwitchScene(SceneID id) override;
	void switchScene();

	void handleEvent(const sf::Event& event);
	void update();
	void render();
};

// 
