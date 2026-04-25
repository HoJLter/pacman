#include "scenes/MenuScene.h"
#include "utils/Log.h"

MenuScene::MenuScene(GameContext& context, ISceneSwitcher& ss):
	Scene(context, ss),
	startButton(
		{20.f, 20.f},
		{500.f, 150.f},
		"LET'S GO!",
		[this]() {
			this->sceneSwitcher.requestSwitchScene(SceneID::Game);
		})
{
	Log::debug(std::to_string(context.settings.viewWidth));
}


void MenuScene::handleEvent(const sf::Event& event){
	startButton.handleEvent(event, context.window);
}


void MenuScene::update() {
	startButton.update(context.window);

}


void MenuScene::render() {
	startButton.render(context.window);
}