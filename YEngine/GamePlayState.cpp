#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "ResourceManager.h"


GamePlayState GamePlayState::sGamePlayState;


void GamePlayState::init()
{
	ResourceManager rm;
	rm.createResource("Resources\\Models\\3x3x3\\3x3x3.obj", RESOURCETYPE::OBJECT, 0);
	rm.createResource("Resources\\Models\\3x3x3\\3x3x3.png", RESOURCETYPE::TEXTURE, 1);
	rm.cleanup();
}

void GamePlayState::cleanup()
{
}

void GamePlayState::pause()
{
}

void GamePlayState::resume()
{
}

void GamePlayState::handleEvents(GameManager * gm)
{
	MSG msg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT) {
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Event event;

	while (Locator::getEventHandler()->pollEvent(event)) {
		if (event.event == EVENT::GAMEOVER) {
			gm->quit();
		}
	}
}

void GamePlayState::update(GameManager * gm)
{
}

void GamePlayState::render(GameManager * gm)
{
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance()
{
	return &sGamePlayState;
}
