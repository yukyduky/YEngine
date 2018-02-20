#pragma once
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <deque>


enum class EVENT { GAMEOVER };


struct Event
{
	EVENT event;
	size_t param;
};

class EventHandler
{
private:
	std::deque<Event> eventQueue;
public:
	bool pollEvent(Event& event);
	void addEvent(Event event);
};

#endif // EVENTHANDLER_H
