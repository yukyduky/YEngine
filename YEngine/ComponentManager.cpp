#include "ComponentManager.h"


void ComponentManager::init()
{
}

size_t ComponentManager::addEntity(std::bitset<BITMASK_SIZE> componentBitmask)
{
	size_t id =  m_Entities.push(std::bitset<BITMASK_SIZE>(0));

	this->addComponentsToEntity(id, componentBitmask);

	return id;
}

void ComponentManager::removeEntity(const size_t entityID)
{
	this->removeComponentsFromEntity(entityID, m_Entities[entityID]);

	m_Entities.remove(entityID);
}

void ComponentManager::addComponentsToEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask)
{
	size_t componentsAdded = 0;
	std::unordered_map<std::bitset<BITMASK_SIZE>, ComponentData>::iterator it = m_Components.begin();

	while (it != m_Components.end() && componentsAdded < componentBitmask.count())
	{
		if (((*it).first & componentBitmask) == (*it).first)
		{
			componentsAdded++;

			Component* component = nullptr;
			(*it).second.mm.requestMemory(component, &(*it).second.templateInstance, (*it).second.byteSize);
			(*it).second.components.push(component);

			m_Entities[entityID] |= (*it).first;
		}

		it++;
	}
}

void ComponentManager::removeComponentsFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask)
{
	size_t componentsRemoved = 0;
	std::unordered_map<std::bitset<BITMASK_SIZE>, ComponentData>::iterator it = m_Components.begin();

	while (it != m_Components.end() && componentsRemoved < componentBitmask.count())
	{
		if (((*it).first & componentBitmask) == (*it).first)
		{
			componentsRemoved++;

			ComponentData& data = m_Components.at(componentBitmask);

			data.mm.releaseMemory(data.components[entityID]);
			data.components.remove(entityID);

			// 00001 -> 11110
			std::bitset<BITMASK_SIZE> notBitmask = ~(*it).first;
			// 01101 & 11110 -> 01100
			m_Entities[entityID] &= notBitmask;
		}

		it++;
	}
}

void ComponentManager::registerComponentType(Component& templateInstance, size_t byteSize, const char* name, size_t maxCapacity, std::bitset<BITMASK_SIZE> componentBitmask)
{
	m_Components.insert(m_Components.end(), std::pair<std::bitset<BITMASK_SIZE>, ComponentData>(componentBitmask, ComponentData(templateInstance, name, byteSize, maxCapacity)));
}

void ComponentManager::unregisterComponentType(std::bitset<BITMASK_SIZE> componentBitmask)
{
	m_Components.at(componentBitmask).mm.cleanup();
	m_Components.erase(componentBitmask);
}

void ComponentManager::cleanup()
{
	for (auto &i : m_Components)
	{
		i.second.mm.cleanup();
	}
	m_Components.clear();
}
