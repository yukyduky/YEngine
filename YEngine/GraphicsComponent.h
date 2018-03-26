#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <unordered_map>
#include <bitset>
#include "Resource.h"

using namespace DirectX::SimpleMath;

class GraphicsComponent : public Component
{
protected:
	Matrix m_World;
	std::bitset<RESOURCETYPE::SIZE> m_ResourceBitmask;
	std::unordered_map<std::bitset<RESOURCETYPE::SIZE>, size_t> m_ResourceIDs;
public:
	virtual void init() override;
	virtual void update(float dt) override;
	virtual void cleanup() override;

	void setResource(std::bitset<RESOURCETYPE::SIZE> resourceBitmask, size_t resourceID);
	void removeResources(std::bitset<RESOURCETYPE::SIZE> resourceBitmask);
	size_t getResourceID(std::bitset<RESOURCETYPE::SIZE> resourceBitmask);
	std::bitset<RESOURCETYPE::SIZE> getResourceBitmask() const;
	Matrix& getWorld();
	void setWorld(Matrix& val);
};

#endif // !GRAPHICSCOMPONENT_H
