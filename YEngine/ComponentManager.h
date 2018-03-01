#pragma once
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <unordered_map>
#include "YUtilityTypes.h"

class ComponentManager
{
private:
	std::unordered_map<size_t, size_t> m_EntityToBitmask;
public:
	void init();

	const size_t addEntity(const size_t componentBitmask);
	void removeEntity(const size_t entityID);
	void addComponentToEntity(const size_t entityID, const size_t componentBitmask);
	void removeComponentFromEntity(const size_t entityID, const size_t componentBitmask);
	void registerComponentType(Byte* templateComponent, size_t componentSize, size_t componentTypeID);
	void unregisterComponentType(size_t componentTypeID);

	void cleanup();
};

#endif // COMPONENTMANAGER_H
