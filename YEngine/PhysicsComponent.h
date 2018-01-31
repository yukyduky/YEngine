#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"

class PhysicsComponent : public Component
{
private:
	Vector3 velocity;
	Vector3 acceleration;
	float weight;
public:
	virtual void receive(Message msg);
	virtual void init(float weight);
	virtual void cleanup();
	virtual void update();
	void setVeloctiy(Vector3 velocity);
	Vector3 getVelocity();
	void setAcceleration(Vector3 acceleration);
	Vector3 getAcceleration();
};

#endif // !PHYSICSCOMPONENT_H
