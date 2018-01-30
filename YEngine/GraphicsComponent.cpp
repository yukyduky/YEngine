#include "GraphicsComponent.h"
#include "GameObject.h"



GraphicsComponent::GraphicsComponent(GameObject& obj) : ID(obj.getID())
{
}

const size_t GraphicsComponent::getID()
{
	return this->ID;
}

void GraphicsComponent::receive(GameObject & obj, Message msg)
{
}

size_t GraphicsComponent::getResourceID()
{
	return this->resourceID;
}
