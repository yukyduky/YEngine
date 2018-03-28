#pragma once
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "IComponentManager.h"
#include <map>
#include <unordered_map>
#include "MemoryManager.h"
#include "IDHandler.h"

class ComponentManager : public IComponentManager
{
private:
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

	idlist<std::bitset<BITMASK_SIZE>> m_Entities;
	std::unordered_map<std::bitset<BITMASK_SIZE>, ComponentData> m_Components;
	IDHandler m_BitmaskIDs;
public:
	void init() override;
	size_t addEntity(std::bitset<BITMASK_SIZE> componentBitmask) override;
	void removeEntity(const size_t entityID) override;
	void addComponentsToEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask) override;
	void removeComponentsFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask) override;
	std::bitset<BITMASK_SIZE> registerComponentType(Component& templateInstance, size_t byteSize, const char* name, size_t maxCapacity) override;
	void unregisterComponentType(std::bitset<BITMASK_SIZE> componentBitmask) override;
	void cleanup() override;

	void getComponentFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask, Component*& component) override;
	void getAllComponentOfType(const std::bitset<BITMASK_SIZE> componentBitmask, idlist<Component*>& components) override;
};

#endif // COMPONENTMANAGER_H
