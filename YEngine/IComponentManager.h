#pragma once
#ifndef ICOMPONENTMANAGER_H
#define ICOMPONENTMANAGER_H

#include <bitset>
#include "IComponentManager.h"
#include "idlist.h"

constexpr size_t BITMASK_SIZE = 32;

namespace YEngine
{
	class Component;

	class IComponentManager
	{
	public:
		virtual void init() = 0;
		virtual size_t addEntity(std::bitset<BITMASK_SIZE> componentBitmask) = 0;
		virtual void removeEntity(const size_t entityID) = 0;
		virtual void addComponentsToEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask) = 0;
		virtual void removeComponentsFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask) = 0;
		virtual std::bitset<BITMASK_SIZE> registerComponentType(Component* templateInstance, size_t byteSize, const char* name, size_t maxCapacity) = 0;
		virtual void unregisterComponentType(std::bitset<BITMASK_SIZE> componentBitmask) = 0;
		virtual void cleanup() = 0;
	
		virtual void getComponentFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask, Component*& component) = 0;
		virtual void getAllComponentOfType(const std::bitset<BITMASK_SIZE> componentBitmask, idlist<Component*>& components) = 0;
	};
}

#endif
