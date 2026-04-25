#include "scenes/MenuScene.h"
#include "utils/Log.h"

MenuScene::MenuScene(GameContext& context, ISceneSwitcher& ss):
	Scene(context, ss),
	startButton(
		{200.f, 20.f},
		{context.settings.viewWidth/2.f, 
		context.settings.viewHeight-200.f},
		"LET'S GO!",
		[this]() {
			this->sceneSwitcher.requestSwitchScene(SceneID::Game);
		},
		context.assetsManager),
	pacmanLabel(
		"PACMAN",
		{ context.settings.viewWidth / 2.f,
		context.settings.viewHeight / 2 - 300.f },
		100,
		sf::Color::Yellow,
		context.assetsManager
	)
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
	pacmanLabel.render(context.window);
	startButton.render(context.window);
}
