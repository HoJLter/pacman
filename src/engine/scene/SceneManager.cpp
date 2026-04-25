#include <memory>
#include "engine/scene/SceneManager.h"
#include "utils/Log.h"

std::string sceneIdToStr(SceneID id) {
	switch (id) {
	case SceneID::Menu:  return "MenuScene";
	case SceneID::Game: return "GameScene";
	default: return "UnknownScene";
	}
}

SceneManager::SceneManager(sf::RenderWindow& window, AssetsManager& am): 
	window(window),
	assetsManager(am){
	curScene = std::make_unique<MenuScene>(window.getSize(), *this, assetsManager);
}

void SceneManager::requestSwitchScene(SceneID id) {
	Log::debug("New scene switch request: " + sceneIdToStr(id));
	requestedScene = id;
}

void SceneManager::switchScene() {
	if (requestedScene.has_value()) {
		switch (requestedScene.value()) {
		case SceneID::Menu: {
			curScene = std::make_unique<MenuScene>(window.getSize(), *this, assetsManager);
			break;
		}
		case SceneID::Game: {
			curScene = std::make_unique<GameScene>(window.getSize(), *this, assetsManager);
			break;
		}
		}
		Log::debug("Scene has been switched to " + sceneIdToStr(requestedScene.value()));
		requestedScene.reset();
	}
}

void SceneManager::handleEvent(const sf::Event& event) {
	curScene->handleEvent(event, window);
	switchScene();
}

void SceneManager::update() {
	curScene->update(window);
	switchScene();
}

void SceneManager::render() {
	curScene->render(window);
}