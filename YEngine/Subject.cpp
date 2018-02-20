#include "Subject.h"
#include "Observer.h"
#include "GameObject.h"



void Subject::notify(const GameObject& obj, size_t eventID)
{
	for (auto &i : this->observers) {
		i.second->onNotify(obj, eventID);
	}
}

void Subject::addObserver(Observer * obs, size_t ID)
{
	this->observers.insert(this->observers.end(), std::pair<size_t, Observer*>(ID, obs));
}

void Subject::removeObserver(size_t ID)
{
	std::map<size_t, Observer*>::iterator it = this->observers.find(ID);
	if (it != this->observers.end()) {
		this->observers.erase(it);
	}
}
