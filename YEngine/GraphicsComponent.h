#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include <d3d11.h>

class GraphicsComponent : public Component
{
private:
	const size_t ID;
	size_t resourceID;
public:
	GraphicsComponent(GameObject& obj);
	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual size_t getResourceID();
};

#endif // !GRAPHICSCOMPONENT_H
