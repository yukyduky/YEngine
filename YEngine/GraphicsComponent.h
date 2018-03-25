#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

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
