#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"

class GraphicsComponent : public Component
{
protected:
	Matrix m_World;
public:
	virtual void init();
	virtual void cleanup();
	virtual void update();
};

#endif // !GRAPHICSCOMPONENT_H
