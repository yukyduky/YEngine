#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"


GamePlayState GamePlayState::sGamePlayState;


void GamePlayState::init()
{
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
