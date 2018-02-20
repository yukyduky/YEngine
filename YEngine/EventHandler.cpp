#include "EventHandler.h"



bool EventHandler::pollEvent(Event & event)
{
	bool eventExists = false;

	if (!this->eventQueue.empty()) {
		eventExists = true;
		event = this->eventQueue.front();
		this->eventQueue.pop_front();
	}

	return eventExists;
}

void EventHandler::addEvent(Event event)
{
	this->eventQueue.push_back(event);
}
