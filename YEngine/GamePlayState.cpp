#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "ResourceManager.h"
#include "MemoryManager.h"


GamePlayState GamePlayState::ms_GamePlayState;


void GamePlayState::init()
{
	m_FrameMemory = new MemoryManager(16, 100);
	Locator::provide(m_FrameMemory, MEMORYTYPE::FRAME);
}

void GamePlayState::cleanup()
{
	m_FrameMemory->cleanup();
	delete m_FrameMemory;
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
			m_GameObjects[event.param]->cleanup();
			delete m_GameObjects[event.param];
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
	return &ms_GamePlayState;
}
