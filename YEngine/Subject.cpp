#include "Subject.h"
#include "Observer.h"
#include "GameObject.h"



void Subject::notify(const GameObject& obj, size_t eventID)
{
	for (auto &i : m_Observers)
	{
		i.second->onNotify(obj, eventID);
	}
}

void Subject::addObserver(Observer * obs, size_t ID)
{
	m_Observers.insert(m_Observers.end(), std::pair<size_t, Observer*>(ID, obs));
}

void Subject::removeObserver(size_t ID)
{
	std::map<size_t, Observer*>::iterator it = m_Observers.find(ID);
	if (it != m_Observers.end())
	{
		m_Observers.erase(it);
	}
}
