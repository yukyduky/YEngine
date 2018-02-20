#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H

#include <map>

class GameObject;
class Observer;

class Subject
{
private:
	std::map<size_t, Observer*> observers;
public:
	void notify(const GameObject& obj, size_t eventID);
	void addObserver(Observer* obs, size_t ID);
	void removeObserver(size_t ID);
};

#endif // SUBJECT_H
