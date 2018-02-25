#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"

class PhysicsComponent : public Component
{
private:
	Vector3 m_Velocity;
	Vector3 m_Acceleration;
	float m_Weight;
public:
	virtual void receive(Message msg);
	virtual void init();
	virtual void cleanup();
	virtual void update();
	void setup(float weight);
	void setVeloctiy(Vector3 velocity);
	Vector3 getVelocity();
	void setAcceleration(Vector3 acceleration);
	Vector3 getAcceleration();
};

#endif // !PHYSICSCOMPONENT_H
