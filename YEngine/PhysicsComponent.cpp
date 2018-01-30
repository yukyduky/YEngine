#include "PhysicsComponent.h"
#include "GameObject.h"


PhysicsComponent::PhysicsComponent(GameObject & obj)
{
}

const size_t PhysicsComponent::getID()
{
	return size_t();
}

void PhysicsComponent::receive(GameObject & obj, Message msg)
{
}
