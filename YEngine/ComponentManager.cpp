#include "ComponentManager.h"



void ComponentManager::init()
{

}

const size_t ComponentManager::addEntity(const size_t componentBitmask)
{
	return componentBitmask;
}

void ComponentManager::removeEntity(const size_t entityID)
{

}

void ComponentManager::addComponentToEntity(const size_t entityID, const size_t componentBitmask)
{

}

void ComponentManager::removeComponentFromEntity(const size_t entityID, const size_t componentBitmask)
{

}

void ComponentManager::registerComponentType(Byte* templateComponent, size_t componentSize, size_t componentTypeID)
{

}

void ComponentManager::unregisterComponentType(size_t componentTypeID)
{

}

void ComponentManager::cleanup()
{

}
