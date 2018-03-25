#include "StateManager.h"
#include "State.h"

std::vector<State*> StateManager::m_sStates;

void StateManager::changeState(State* state)
{ 
	// If the state stack isn't empty
	if (!m_sStates.empty())
	{
		// Cleanup the latest stack at the back
		m_sStates.back()->cleanup();
		// Remove the state from the back of the stack
		m_sStates.pop_back();
	}
	// Add the new state to the back of the stack
	m_sStates.push_back(state);
	// Initialize the new state
	m_sStates.back()->init();
}

void StateManager::popState()
{
	// If the state stack isn't empty
	if (!m_sStates.empty())
	{
		// Cleanup the latest stack at the back
		m_sStates.back()->cleanup();
		// Remove the state from the back of the stack
		m_sStates.pop_back();
		// If the state stack still isn't empty
		if (!m_sStates.empty())
		{
			// Resume the latest state at the back
			m_sStates.back()->resume();
		}
	}
}

void StateManager::pushState(State* state)
{ 
	// If the state stack isn't empty
	if (!m_sStates.empty())
	{
		// Pause the current state
		m_sStates.back()->pause();
	}
	// Add the new state to the back of the stack
	m_sStates.push_back(state);
	// Initialize the new state
	m_sStates.back()->init();
}

void StateManager::handleEvents(GameManager* gm)
{
	m_sStates.back()->handleEvents(gm);
}

void StateManager::update(GameManager* gm)
{
	m_sStates.back()->update(gm);
}

void StateManager::render(GameManager* gm)
{
	m_sStates.back()->render(gm);
}

void StateManager::cleanup()
{
	for (auto &i : m_sStates)
	{
		i->cleanup();
	}
}
