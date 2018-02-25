#include "EventHandler.h"



bool EventHandler::pollEvent(Event & event)
{
	bool eventExists = false;

	if (!m_EventQueue.empty())
	{
		eventExists = true;
		event = m_EventQueue.front();
		m_EventQueue.pop_front();
	}

	return eventExists;
}

void EventHandler::addEvent(Event event)
{
	m_EventQueue.push_back(event);
}
