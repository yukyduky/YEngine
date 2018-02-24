#include "GameManager.h"
#include "StateManager.h"
#include "State.h"
#include "Locator.h"
#include "GameTime.h"
#include "GamePlayState.h"
#include "ConfigHandler.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "MemoryManager.h"



void GameManager::init(HINSTANCE hInstance, int nCmdShow)
{
	this->isRunning = true;

	this->defRenderer.init();
	
	Locator::getMemoryManager(MEMORYTYPE::PERM)->requestMemory(this->gameTime, &GameTime(), sizeof(GameTime));
	Locator::provide(this->gameTime);

	Locator::getMemoryManager(MEMORYTYPE::PERM)->requestMemory(this->configHandler, &ConfigHandler(), sizeof(ConfigHandler));
	Locator::provide(this->configHandler);

	Locator::getMemoryManager(MEMORYTYPE::PERM)->requestMemory(this->eventHandler, &EventHandler(), sizeof(EventHandler));
	Locator::provide(this->eventHandler);

	this->stateMemory = new MemoryManager(16, 100);
	Locator::provide(this->stateMemory, MEMORYTYPE::STATE);

	// Start the game timer
	Locator::getGameTime()->StartTimer();

	// Set the first state of the game
	StateManager::changeState(GamePlayState::getInstance());
}

void GameManager::cleanup()
{
	this->defRenderer.cleanup();
	this->stateMemory->cleanup();
	delete this->stateMemory;
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
	this->defRenderer.firstpass();
	StateManager::render(this);
}

void GameManager::display(State* state)
{
	this->defRenderer.secondpass();
}

bool GameManager::getIsRunning()
{
	return this->isRunning;
}

void GameManager::quit()
{
	this->isRunning = false;
	StateManager::cleanup();
}
