#pragma once
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "IEventHandler.h"
#include <deque>

class EventHandler : public IEventHandler
{
private:
	std::deque<Event> m_EventQueue;
public:
	virtual ~EventHandler() {}
	bool pollEvent(Event& event) override;
	void addEvent(Event event) override;
};

#endif // EVENTHANDLER_H
