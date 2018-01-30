#include "CollisionComponent.h"
#include "GameObject.h"



CollisionComponent::CollisionComponent(GameObject & obj)
{
}

const size_t CollisionComponent::getID()
{
	return size_t();
}

void CollisionComponent::receive(GameObject & obj, Message msg)
{
}
