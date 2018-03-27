#include "ComponentManager.h"
#include <intrin.h>
#include <cassert>


void ComponentManager::init()
{
	m_BitmaskIDs.resize(BITMASK_SIZE, 0);
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

std::bitset<BITMASK_SIZE> ComponentManager::registerComponentType(Component& templateInstance, size_t byteSize, const char* name, size_t maxCapacity)
{
	assert(m_BitmaskIDs.peekNextID() != BITMASK_SIZE && "Tried to register one too many component types");
	size_t id = m_BitmaskIDs.getNewID();
	std::bitset<BITMASK_SIZE> componentBitmask(1ULL << id);

	m_Components.insert(m_Components.end(), std::pair<std::bitset<BITMASK_SIZE>, ComponentData>(componentBitmask, ComponentData(templateInstance, name, byteSize, maxCapacity)));

	return componentBitmask;
}

void ComponentManager::unregisterComponentType(std::bitset<BITMASK_SIZE> componentBitmask)
{
	m_Components.at(componentBitmask).mm.cleanup();
	m_Components.erase(componentBitmask);

	unsigned long id;
	_BitScanForward(&id, componentBitmask.to_ulong()); // TODO::YE: Make compatible with other compilers)
	m_BitmaskIDs.remove(id);
}

void ComponentManager::cleanup()
{
	for (auto &i : m_Components)
	{
		i.second.mm.cleanup();
	}
	m_Components.clear();
}
