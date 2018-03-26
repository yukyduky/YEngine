#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"
#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class PhysicsComponent : public Component
{
private:
	Vector3 m_Velocity;
	Vector3 m_Acceleration;
public:
	virtual ~PhysicsComponent() {}

	void init() override;
	void update(float dt) override;
	void cleanup() override;

	Vector3 getVelocity() const;
	void setVelocity(Vector3 val);
	Vector3 getAcceleration() const;
	void setAcceleration(Vector3 val);
};

#endif // PHYSICSCOMPONENT_H
