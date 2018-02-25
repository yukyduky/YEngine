#include "StateManager.h"
#include "State.h"

std::vector<State*> StateManager::ms_States;

void StateManager::changeState(State* state)
{ 
	// If the state stack isn't empty
	if (!ms_States.empty())
	{
		// Cleanup the latest stack at the back
		ms_States.back()->cleanup();
		// Remove the state from the back of the stack
		ms_States.pop_back();
	}
	// Add the new state to the back of the stack
	ms_States.push_back(state);
	// Initialize the new state
	ms_States.back()->init();
}

void StateManager::popState()
{
	// If the state stack isn't empty
	if (!ms_States.empty())
	{
		// Cleanup the latest stack at the back
		ms_States.back()->cleanup();
		// Remove the state from the back of the stack
		ms_States.pop_back();
		// If the state stack still isn't empty
		if (!ms_States.empty())
		{
			// Resume the latest state at the back
			ms_States.back()->resume();
		}
	}
}

void StateManager::pushState(State* state)
{ 
	// If the state stack isn't empty
	if (!ms_States.empty())
	{
		// Pause the current state
		ms_States.back()->pause();
	}
	// Add the new state to the back of the stack
	ms_States.push_back(state);
	// Initialize the new state
	ms_States.back()->init();
}

void StateManager::handleEvents(GameManager* gm)
{
	ms_States.back()->handleEvents(gm);
}

void StateManager::update(GameManager* gm)
{
	ms_States.back()->update(gm);
}

void StateManager::render(GameManager* gm)
{
	ms_States.back()->render(gm);
}

void StateManager::cleanup()
{
	for (auto &i : ms_States)
	{
		i->cleanup();
	}
}
