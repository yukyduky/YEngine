#include "CollisionComponent.h"
#include "GameObject.h"


void CollisionComponent::receive(Message msg)
{
}

void CollisionComponent::init()
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

void CollisionComponent::setup(PhysicsComponent * physics, float width, float height)
{
	this->physics_ = physics;

	this->init();
}
