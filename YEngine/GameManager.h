#pragma once
#ifndef RANDOMZENGINE_H
#define RANDOMZENGINE_H

#include <Windows.h>
#include <d3d11.h>
#include "IGameTime.h"
#include "DeferredRenderer.h"
#include "IConfigHandler.h"
#include "IEventHandler.h"
#include "idlist.h"

class GameObject;
class State;

class GameManager
{
private:
	bool isRunning;
	IGameTime* gameTime;
	IConfigHandler* configHandler;
	IEventHandler* eventHandler;
	DeferredRenderer defRenderer;

	idlist<GameObject*> gameObjects;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	Creates and initiates all the tools and sets the first state*/
	void init(HINSTANCE hInstance, int nCmdShow);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	Cleans up all the memory used by GameManager
	*/
	void cleanup();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Change the current state.
	2. Passes the 'State'(class) object as a parameter.
	*/
	void changeState(State* state);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calls the 'handleEvents()' function found within the 'StateManager'(class).
	*/
	void handleEvents();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Poll for new events via the 'PeekMessage()' function.
	2. Passes the 'MSG'(class) object as a parameter.
	*/
	bool pollEvent(MSG &msg);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Updates the game depending on the current state.
	2. Simply runs the 'StateManager'(class) 'update()' function.
	*/
	void update();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Renders the scene according to the current state.
	2. Runs the 'StateManager'(class) 'render()' function.
	*/
	void render();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Clears, draws, and displays the current state.
	*/
	void display(State* state);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the 'isRunning'(obj) boolean, to see if the game is currently running.
	*/
	bool getIsRunning();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Sets the 'isRunning'(obj) boolean to false, closing the game.
	*/
	void quit();
};

#endif
