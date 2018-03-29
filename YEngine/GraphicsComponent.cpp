#include "GraphicsComponent.h"



GraphicsComponent::GraphicsComponent()
{
	m_ResourceBitmask = 0;
	m_RenderDepth = 0;
}

void GraphicsComponent::init()
{
}

void GraphicsComponent::init(size_t renderDepth, Matrix& world)
{
	m_RenderDepth = renderDepth;
	m_World = world;
}

void GraphicsComponent::update(float dt)
{
}

void GraphicsComponent::cleanup()
{
	m_ResourceBitmask = 1 << 0;
	m_ResourceIDs.clear();
}

void GraphicsComponent::setResource(std::bitset<RESOURCETYPE::SIZE> resourceBitmask, size_t resourceID)
{
	if (resourceBitmask.count() == 1)
	{
		//m_ResourceIDs[resourceBitmask]; = resourceID;
		m_ResourceIDs.insert(m_ResourceIDs.end(), std::pair<std::bitset<RESOURCETYPE::SIZE>, size_t>(resourceBitmask, resourceID));

		m_ResourceBitmask |= resourceBitmask;
	}
}

void GraphicsComponent::removeResources(std::bitset<RESOURCETYPE::SIZE> resourceBitmask)
{
	size_t resourcesRemoved = 0;
	std::unordered_map<std::bitset<RESOURCETYPE::SIZE>, size_t>::iterator it = m_ResourceIDs.begin();

	while (it != m_ResourceIDs.end() && resourcesRemoved < resourceBitmask.count())
	{
		if (((*it).first & resourceBitmask) == (*it).first)
		{
			resourcesRemoved++;

			(*it).second = -1;

			std::bitset<RESOURCETYPE::SIZE> removedBitmask = ~(*it).first;
			m_ResourceBitmask &= removedBitmask;
		}

		it++;
	}
}

size_t GraphicsComponent::getResourceID(std::bitset<RESOURCETYPE::SIZE> resourceBitmask)
{
	size_t id = -1;

	if (resourceBitmask.count() == 1 && (resourceBitmask & m_ResourceBitmask) == resourceBitmask)
	{
		id = m_ResourceIDs[resourceBitmask];
	}

	return id;
}

std::bitset<RESOURCETYPE::SIZE> GraphicsComponent::getResourceBitmask() const
{
	return m_ResourceBitmask;
}

Matrix& GraphicsComponent::getWorld()
{
	return m_World;
}

void GraphicsComponent::setWorld(Matrix& val)
{
	m_World = val;
}

size_t GraphicsComponent::getRenderDepth() const
{
	return m_RenderDepth;
}

void GraphicsComponent::setRenderDepth(size_t val)
{
	m_RenderDepth = val;
}
