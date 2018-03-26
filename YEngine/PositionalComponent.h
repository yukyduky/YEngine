#pragma once
#ifndef POSITIONALCOMPONENT_H
#define POSITIONALCOMPONENT_H

#include "Component.h"
#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class PositionalComponent : public Component
{
private:
	Vector3 m_Position;
public:
	virtual ~PositionalComponent() {}

	virtual void init() override;
	virtual void update() override;
	virtual void cleanup() override;

	Vector3 getPosition() const;
	void setPosition(Vector3 val);
};

#endif // POSITIONALCOMPONENT_H
