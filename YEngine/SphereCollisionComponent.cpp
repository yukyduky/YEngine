#include "SphereCollisionComponent.h"
#include "BoxCollisionComponent.h"


void SphereCollisionComponent::init()
{
	m_BSphere.Center = Vector3(0.0f, 0.0f, 0.0f);
	m_BSphere.Radius = 1.0f;
}

void SphereCollisionComponent::update(float dt)
{
}

void SphereCollisionComponent::cleanup()
{
}

bool SphereCollisionComponent::collideWith(CollisionComponent * collision_, BoundingBox & intersectionBox)
{
	return collision_->collideWith(this, intersectionBox);
}

bool SphereCollisionComponent::collideWith(SphereCollisionComponent * sphere_, BoundingBox & intersectionBox)
{
	bool areColliding = false;
	BoundingSphere bSphere = sphere_->getBSphere();

	if (m_BSphere.Intersects(bSphere))
	{
		areColliding = true;

		float combinedRadius = bSphere.Radius + m_BSphere.Radius;
		float xDelta = combinedRadius - abs(bSphere.Center.x - m_BSphere.Center.x);
		float yDelta = combinedRadius - abs(bSphere.Center.y - m_BSphere.Center.y);
		float zDelta = combinedRadius - abs(bSphere.Center.z - m_BSphere.Center.z);
		intersectionBox.Extents = Vector3(xDelta, yDelta, zDelta);

		intersectionBox.Center.x = abs(bSphere.Center.x) < abs(m_BSphere.Center.x) ? bSphere.Center.x : m_BSphere.Center.x;
		intersectionBox.Center.y = abs(bSphere.Center.y) < abs(m_BSphere.Center.y) ? bSphere.Center.y : m_BSphere.Center.y;
		intersectionBox.Center.z = abs(bSphere.Center.z) < abs(m_BSphere.Center.z) ? bSphere.Center.z : m_BSphere.Center.z;

		intersectionBox.Center.x += xDelta / 2;
		intersectionBox.Center.y += yDelta / 2;
		intersectionBox.Center.z += zDelta / 2;
	}

	return areColliding;
}

bool SphereCollisionComponent::collideWith(BoxCollisionComponent * box_, BoundingBox & intersectionBox)
{
	return box_->collideWith(this, intersectionBox);
}

void SphereCollisionComponent::setPosition(Vector3 val)
{
	m_BSphere.Center = val;
}

void SphereCollisionComponent::setRadius(Vector3 val)
{
	m_BSphere.Radius = val.x;
}

BoundingSphere SphereCollisionComponent::getBSphere() const
{
	return m_BSphere;
}

void SphereCollisionComponent::setBSphere(BoundingSphere val)
{
	m_BSphere = val;
}
