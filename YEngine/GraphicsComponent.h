#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"

class GraphicsComponent : public Component
{
protected:
	const size_t ID;
	Matrix world;
public:
	virtual void receive(Message msg);
	virtual void init();
	virtual void cleanup();
	virtual void update();
};

#endif // !GRAPHICSCOMPONENT_H
