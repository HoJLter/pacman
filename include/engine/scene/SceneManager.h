#pragma once
#include <iostream>
#include "Scenes.h"
#include "engine/scene/ISceneSwitcher.h"
#include "engine/assets/AssetsManager.h"
#include <memory>
#include <optional>

std::string sceneIdToStr(SceneID id);

class SceneManager: public ISceneSwitcher {
private:
	std::unique_ptr<Scene> curScene;
	std::optional<SceneID> requestedScene;

	GameContext& context;
	

public:
	SceneManager(GameContext& context);

	void requestSwitchScene(SceneID id) override;
	void switchScene();

	void handleEvent(const sf::Event& event);
	void update();
	void render();
};
