#pragma once
#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

enum class EVENT { GAMEOVER, OBJECTDIED };

struct Event
{
	Event() : param(-1) {}
	Event(EVENT event, size_t param) : event(event), param(param) {}

	EVENT event;
	size_t param;
};

class IEventHandler
{
public:
	virtual ~IEventHandler() {}
	virtual bool pollEvent(Event& event) = 0;
	virtual void addEvent(Event event) = 0;
};

#endif
