#include "GameManager.h"
#include "StateManager.h"
#include "State.h"
#include "Locator.h"
#include "GameTime.h"
#include "GamePlayState.h"
#include "ConfigHandler.h"
#include "EventHandler.h"


void GameManager::init(HINSTANCE hInstance, int nCmdShow)
{
	this->isRunning = true;

	this->defRenderer.init();
	
	this->gameTime = new GameTime;
	Locator::provide(this->gameTime);

	this->configHandler = new ConfigHandler;
	Locator::provide(this->configHandler);

	this->eventHandler = new EventHandler;
	Locator::provide(this->eventHandler);

	// Start the game timer
	Locator::getGameTime()->StartTimer();

	// Set the first state of the game
	StateManager::changeState(GamePlayState::getInstance());
}

void GameManager::cleanup()
{
	delete this->gameTime;
	delete this->configHandler;
	this->defRenderer.cleanup();
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
