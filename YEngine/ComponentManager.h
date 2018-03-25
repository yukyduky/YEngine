#pragma once
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <unordered_map>
#include <bitset>
#include "Component.h"
#include "MemoryManager.h"
#include "idlist.h"

#define BITMASK_SIZE 32

struct ComponentData
{
	MemoryManager mm;
	idlist<Component*> components;

	Component& templateInstance;
	const char* name;
	size_t byteSize;

	ComponentData(Component& templateInstance, const char* name, size_t byteSize, size_t maxCapacity) :
		templateInstance(templateInstance), name(name), byteSize(byteSize), mm(byteSize, maxCapacity), components(maxCapacity) {}
};

class ComponentManager
{
private:
	idlist<std::bitset<BITMASK_SIZE>> m_Entities;
	std::unordered_map<std::bitset<BITMASK_SIZE>, ComponentData> m_Components;
public:
	void init();

	size_t addEntity(std::bitset<BITMASK_SIZE> componentBitmask);
	void removeEntity(const size_t entityID);
	void addComponentsToEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask);
	void removeComponentsFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask);
	void registerComponentType(Component& templateInstance, size_t byteSize, const char* name, size_t maxCapacity, std::bitset<BITMASK_SIZE> componentBitmask);
	void unregisterComponentType(std::bitset<BITMASK_SIZE> componentBitmask);

	template<typename Derived>
	void getComponentFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask, Derived*& component);
	template<typename Derived>
	void getAllComponentOfType(const std::bitset<BITMASK_SIZE> componentBitmask, idlist<Derived*>& components);

	void cleanup();
};

#endif // COMPONENTMANAGER_H

template<typename Derived>
inline void ComponentManager::getComponentFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask, Derived*& component)
{
	component = static_cast<Derived*>(m_Components.at(componentBitmask).components[entityID]);
}

template<typename Derived>
inline void ComponentManager::getAllComponentOfType(const std::bitset<BITMASK_SIZE> componentBitmask, idlist<Derived*>& derivedComponents)
{
	idlist<Component*>& components = m_Components.at(componentBitmask).components;
	size_t numberOfComponents = components.size();

	derivedComponents.reserve(numberOfComponents);
	for (size_t i = 0; i < numberOfComponents; i++)
	{
		derivedComponents.push(static_cast<Derived*>(components[i]));
	}
}
