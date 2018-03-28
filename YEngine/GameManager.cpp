#include "GameManager.h"
#include "StateManager.h"
#include "State.h"
#include "Locator.h"
#include "GameTime.h"
#include "GamePlayState.h"
#include "ConfigHandler.h"
#include "EventHandler.h"
#include "MemoryManager.h"
#include "YEngine.h"


GameManager::GameManager()
{
	m_IsRunning = true;
}

void GameManager::init()
{
	

	Locator::getMemoryManager(MEMORYTYPE::PERM)->requestMemory(m_GameTime, &GameTime(), sizeof(GameTime));
	Locator::provide(m_GameTime);

	Locator::getMemoryManager(MEMORYTYPE::PERM)->requestMemory(m_ConfigHandler, &ConfigHandler(), sizeof(ConfigHandler));
	Locator::provide(m_ConfigHandler);

	Locator::getMemoryManager(MEMORYTYPE::PERM)->requestMemory(m_EventHandler, &EventHandler(), sizeof(EventHandler));
	Locator::provide(m_EventHandler);

	m_StateMemory = new MemoryManager(16, 100);
	Locator::provide(m_StateMemory, MEMORYTYPE::STATE);

	Locator::getGameTime()->StartTimer();

	StateManager::changeState(GamePlayState::getInstance());
}

void GameManager::cleanup()
{
	m_StateMemory->cleanup();
	delete m_StateMemory;
}

void GameManager::changeState(State* state)
{
	StateManager::changeState(state);
}

void GameManager::handleEvents()
{
	StateManager::handleEvents(this);
}

bool GameManager::pollEvent(MSG &msg)
{
	return PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
}

void GameManager::update()
{
	StateManager::update(this);
}

void GameManager::render()
{
	StateManager::render(this);
}

void GameManager::display(State* state)
{
	YEngine::render();
}

bool GameManager::getIsRunning()
{
	return m_IsRunning;
}

void GameManager::quit()
{
	m_IsRunning = false;
	StateManager::cleanup();
}
