#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "ResourceManager.h"
#include "MemoryManager.h"


GamePlayState GamePlayState::sGamePlayState;


void GamePlayState::init()
{
	this->frameMemory = new MemoryManager(16, 100);
	Locator::provide(this->frameMemory, MEMORYTYPE::FRAME);
}

void GamePlayState::cleanup()
{
	this->frameMemory->cleanup();
	delete this->frameMemory;
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

	while (gm->pollEvent(msg))
	{
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT)
		{
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Event event;

	while (Locator::getEventHandler()->pollEvent(event))
	{
		if (event.event == EVENT::GAMEOVER)
		{
			gm->quit();
		}
		else if (event.event == EVENT::OBJECTDIED)
		{
			this->gameObjects[event.param]->cleanup();
			delete this->gameObjects[event.param];
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
