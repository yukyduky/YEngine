#include "CollisionComponent.h"
#include "GameObject.h"


void CollisionComponent::receive(Message msg)
{
}

void CollisionComponent::init()
{
	m_BBox.Center = this->getHead()->getPosition();
}

void CollisionComponent::cleanup()
{
}

void CollisionComponent::update()
{
	m_BBox.Center = this->getHead()->getPosition();
}

void CollisionComponent::setup(PhysicsComponent * physics, float width, float height)
{
	m_Physics = physics;

	this->init();
}
