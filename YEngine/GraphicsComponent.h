#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include "ResourceManager.h"

class GraphicsComponent : public Component
{
protected:
	const size_t ID;
	RESOURCEID resourceID;
	Matrix world;
public:
	virtual void receive(Message msg);
	virtual void init();
	virtual void cleanup();
	virtual void update();
	void setup(RESOURCEID resourceID);
	RESOURCEID getResourceID();
};

#endif // !GRAPHICSCOMPONENT_H
