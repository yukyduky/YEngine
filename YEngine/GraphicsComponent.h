#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include <unordered_map>
#include <bitset>
#include "Resource.h"

class GraphicsComponent : public YEngine::DerivedComponent<GraphicsComponent>
{
protected:
	Matrix m_World;
	size_t m_RenderDepth;
	std::bitset<RESOURCETYPE::SIZE> m_ResourceBitmask;
	std::unordered_map<std::bitset<RESOURCETYPE::SIZE>, size_t> m_ResourceIDs;
public:
	GraphicsComponent();
	virtual ~GraphicsComponent() {}

	virtual void init() override;
	void init(size_t renderDepth, Matrix& world);
	virtual void update(float dt) override;
	virtual void cleanup() override;

	void setResource(std::bitset<RESOURCETYPE::SIZE> resourceBitmask, size_t resourceID);
	void removeResources(std::bitset<RESOURCETYPE::SIZE> resourceBitmask);
	size_t getResourceID(std::bitset<RESOURCETYPE::SIZE> resourceBitmask);
	std::bitset<RESOURCETYPE::SIZE> getResourceBitmask() const;
	Matrix& getWorld();
	void setWorld(Matrix& val);
	size_t getRenderDepth() const;
	void setRenderDepth(size_t val);
};

#endif // !GRAPHICSCOMPONENT_H
