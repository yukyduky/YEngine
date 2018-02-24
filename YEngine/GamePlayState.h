#pragma once
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"
#include <vector>
#include <array>
#include "Command.h"
#include "GameObject.h"
#include "MemoryManager.h"

class Command;
class InputComponent;

class GamePlayState : public State
{
private:
	static GamePlayState sGamePlayState;

	MemoryManager* frameMemory;

	std::vector<GameObject*> gameObjects;

public:
	virtual void init();
	virtual void cleanup();
	virtual void pause();
	virtual void resume();
	virtual void handleEvents(GameManager* gm);
	virtual void update(GameManager* gm);
	virtual void render(GameManager* gm);
	static GamePlayState* getInstance();
};

#endif // !GAMEPLAYSTATE_H
