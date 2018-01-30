#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(GameObject& obj);
	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
};

#endif // !PHYSICSCOMPONENT_H
