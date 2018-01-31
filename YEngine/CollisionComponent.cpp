#include "CollisionComponent.h"
#include "GameObject.h"


void CollisionComponent::receive(Message msg)
{
}

void CollisionComponent::init(float width, float height)
{
	this->bBox.Center = this->getHead()->getPosition();
}

void CollisionComponent::cleanup()
{
}

void CollisionComponent::update()
{
	this->bBox.Center = this->getHead()->getPosition();
}

bool CollisionComponent::intersects(BoundingBox bBox)
{
	bool doesIntersect = false;
	if (bBox.Intersects(bBox)) {
		doesIntersect = true;
	}
	return doesIntersect;
}
