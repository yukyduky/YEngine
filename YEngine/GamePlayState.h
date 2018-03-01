#pragma once
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"
#include "MemoryManager.h"

class Command;
class InputComponent;

class GamePlayState : public State
{
private:
	static GamePlayState ms_GamePlayState;

	MemoryManager* m_FrameMemory;
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
