#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include "ResourceManager.h"

class GraphicsComponent : public Component
{
protected:
	const size_t ID;
	RESOURCEGRAPHIC::ID renderTexID;
	RESOURCEOBJECT::ID renderObjID;
	Matrix world;
public:
	virtual void receive(Message msg);
	virtual void init();
	virtual void cleanup();
	virtual void update();
	void setup(RESOURCEOBJECT::ID resourceID);
	RESOURCEGRAPHIC::ID getRenderTexID();
	RESOURCEOBJECT::ID getRenderObjID();
};

#endif // !GRAPHICSCOMPONENT_H
