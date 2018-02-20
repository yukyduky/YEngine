#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H

class GameObject;

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(const GameObject& obj, size_t eventID) = 0;
};

#endif // OBSERVER_H
