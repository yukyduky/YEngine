#pragma once
#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"
#include <DirectXCollision.h>

class CollisionComponent : public Component
{
private:
	BoundingBox bBox;
public:
	CollisionComponent(GameObject& obj);
	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
};

#endif // !COLLISIONCOMPONENT_H
