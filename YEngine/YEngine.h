#pragma once
#ifndef API_H
#define API_H

#include "IResourceManager.h"
#include "IComponentManager.h"

enum class RENDERER {
	DEFERRED, FORWARD
};

namespace YEngine
{
	void init(RENDERER rendererType, HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed);
	void render();
	void cleanup();

	template<typename Derived>
	void getComponentFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask, Derived*& component);
	template<typename Derived>
	void getAllComponentOfType(const std::bitset<BITMASK_SIZE> componentBitmask, idlist<Derived*>& components);

	IResourceManager* getResourceManager();
	IComponentManager* getComponentManager();

	template<typename Derived>
	void getComponentFromEntity(const size_t entityID, const std::bitset<BITMASK_SIZE> componentBitmask, Derived*& component)
	{
		component = static_cast<Derived*>(getComponentManager()->getComponentFromEntity(entityID, componentBitmask, component));
	}
	template<typename Derived>
	void getAllComponentOfType(const std::bitset<BITMASK_SIZE> componentBitmask, idlist<Derived*>& derivedComponents)
	{
		idlist<Components*> components;
		getComponentManager()->getAllComponentOfType(componentBitmask, components);

		size_t numberOfComponents = components.size();
		derivedComponents.reserve(numberOfComponents);
		for (size_t i = 0; i < numberOfComponents; i++)
		{
			derivedComponents.push(static_cast<Derived*>(components[i]));
		}
	}
}

#endif // API_H
