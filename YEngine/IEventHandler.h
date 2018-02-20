#pragma once
#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

enum class EVENT { GAMEOVER };

struct Event
{
	EVENT event;
	size_t param;
};

class IEventHandler
{
public:
	virtual bool pollEvent(Event& event) = 0;
	virtual void addEvent(Event event) = 0;
};

#endif
