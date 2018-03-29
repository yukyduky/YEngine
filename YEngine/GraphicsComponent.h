#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include <unordered_map>
#include <bitset>
#include "Resource.h"

namespace RENDERRESOURCE {
	enum TYPE {
		DIFFUSE, NORMAL, SPECTRAL, EMISSION, OBJECT, SIZE
	};
}

class GraphicsComponent : public YEngine::DerivedComponent<GraphicsComponent>
{
protected:
	Matrix m_World;
	size_t m_RenderDepth;
	std::bitset<RENDERRESOURCE::SIZE> m_ResourceBitmask;
	std::unordered_map<std::bitset<RENDERRESOURCE::SIZE>, size_t> m_ResourceIDs;
public:
	GraphicsComponent();
	virtual ~GraphicsComponent() {}

	virtual void init() override;
	void init(size_t renderDepth, Matrix& world);
	virtual void update(float dt) override;
	virtual void cleanup() override;

	void addResource(RENDERRESOURCE::TYPE type, size_t id);
	void removeResources(std::bitset<RENDERRESOURCE::SIZE> resourceBitmask);
	size_t getResourceID(RENDERRESOURCE::TYPE type);
	std::bitset<RENDERRESOURCE::SIZE> getResourceBitmask() const;
	Matrix& getWorld();
	void setWorld(Matrix& val);
	size_t getRenderDepth() const;
	void setRenderDepth(size_t val);
};

#endif // !GRAPHICSCOMPONENT_H
