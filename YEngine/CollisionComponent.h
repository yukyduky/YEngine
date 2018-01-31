#pragma once
#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"

class PhysicsComponent;

class CollisionComponent : public Component
{
protected:
	PhysicsComponent* physics_;
	BoundingBox bBox;
public:
	virtual void receive(Message msg);
	virtual void init();
	virtual void cleanup();
	virtual void update();
	virtual void setup(PhysicsComponent* physics, float width, float height);
	virtual void intersects(CollisionComponent* collision_) = 0;
};

#endif // !COLLISIONCOMPONENT_H
