#include "BoxCollisionComponent.h"
#include "SphereCollisionComponent.h"


void BoxCollisionComponent::init()
{
	m_BBox.Center = Vector3(0.0f, 0.0f, 0.0f);
	m_BBox.Extents = Vector3(1.0f, 1.0f, 1.0f);
}

void BoxCollisionComponent::update(float dt)
{
}

void BoxCollisionComponent::cleanup()
{
}

bool BoxCollisionComponent::collideWith(CollisionComponent * collision_, BoundingBox & intersectionBox)
{
	return collision_->collideWith(this, intersectionBox);
}

bool BoxCollisionComponent::collideWith(SphereCollisionComponent * sphere_, BoundingBox & intersectionBox)
{
	bool areColliding = false;

	if (m_BBox.Intersects(sphere_->getBSphere()))
	{
		areColliding = true;


	}

	return areColliding;
}

bool BoxCollisionComponent::collideWith(BoxCollisionComponent * box_, BoundingBox & intersectionBox)
{
	bool areColliding = false;

	if (m_BBox.Intersects(box_->getBBox()))
	{
		areColliding = true;


	}

	return areColliding;
}

void BoxCollisionComponent::setPosition(Vector3 val)
{
	m_BBox.Center = val;
}

void BoxCollisionComponent::setRadius(Vector3 val)
{
	m_BBox.Extents = val;
}

BoundingBox BoxCollisionComponent::getBBox() const
{
	return m_BBox;
}

void BoxCollisionComponent::setBBox(BoundingBox val)
{
	m_BBox = val;
}
