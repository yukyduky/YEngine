#pragma once
#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"

class PhysicsComponent;

class CollisionComponent : public Component
{
private:
	PhysicsComponent* physics;
	BoundingBox bBox;
public:
	virtual void receive(Message msg);
	virtual void init(float width, float height);
	virtual void cleanup();
	virtual void update();
	bool intersects(BoundingBox bBox);
};

#endif // !COLLISIONCOMPONENT_H
