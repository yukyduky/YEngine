#pragma once
#ifndef RANDOMZENGINE_H
#define RANDOMZENGINE_H

#include <Windows.h>
#include <d3d11.h>
#include "Renderer.h"
#include "IGameTime.h"
#include "IConfigHandler.h"
#include "IEventHandler.h"
#include "MemoryManager.h"
#include "idlist.h"

class State;

class GameManager
{
private:
	bool m_IsRunning;

	Renderer* m_Renderer;

	IGameTime* m_GameTime;
	IConfigHandler* m_ConfigHandler;
	IEventHandler* m_EventHandler;
	MemoryManager* m_StateMemory;

public:
	GameManager();
	//***********************************************************
	// Method:    init
	// FullName:  GameManager::init
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: HINSTANCE hInstance
	// Parameter: int nCmdShow
	// Description: Creates and initiates all the tools and sets the first state
	//***********************************************************
	void init();

	//***********************************************************
	// Method:    cleanup
	// FullName:  GameManager::cleanup
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Cleans up all the memory used by GameManager
	//***********************************************************
	void cleanup();

	//***********************************************************
	// Method:    changeState
	// FullName:  GameManager::changeState
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: State * state
	// Description: Changes the state to the given state
	//***********************************************************
	void changeState(State* state);

	//***********************************************************
	// Method:    handleEvents
	// FullName:  GameManager::handleEvents
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: All events, that the state cares about, are handled here
	//***********************************************************
	void handleEvents();

	//***********************************************************
	// Method:    pollEvent
	// FullName:  GameManager::pollEvent
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: MSG & msg
	// Description: Polls windows events
	//***********************************************************
	bool pollEvent(MSG &msg);

	//***********************************************************
	// Method:    update
	// FullName:  GameManager::update
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Updates the current state
	//***********************************************************
	void update();

	//***********************************************************
	// Method:    render
	// FullName:  GameManager::render
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Renders the current state
	//***********************************************************
	void render();

	//***********************************************************
	// Method:    display
	// FullName:  GameManager::display
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: State * state
	// Description: Displays the current state
	//***********************************************************
	void display(State* state);

	//***********************************************************
	// Method:    getIsRunning
	// FullName:  GameManager::getIsRunning
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Description: Returns true as long as the game is set to be runnning
	//***********************************************************
	bool getIsRunning();

	//***********************************************************
	// Method:    quit
	// FullName:  GameManager::quit
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Sets isRunning to false and exits the game loop on the start of the next loop
	//***********************************************************
	void quit();
};

#endif
