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
	BoundingSphere bSphere = sphere_->getBSphere();

	if (m_BBox.Intersects(bSphere))
	{
		areColliding = true;

		Vector3 combinedRadiuses = Vector3(m_BBox.Extents.x + bSphere.Radius, m_BBox.Extents.y + bSphere.Radius, m_BBox.Extents.z + bSphere.Radius);
		float xDelta = combinedRadiuses.x - abs(m_BBox.Center.x - bSphere.Center.x);
		float yDelta = combinedRadiuses.y - abs(m_BBox.Center.y - bSphere.Center.y);
		float zDelta = combinedRadiuses.z - abs(m_BBox.Center.z - bSphere.Center.z);
		intersectionBox.Extents = Vector3(xDelta, yDelta, zDelta);
		
		intersectionBox.Center.x = abs(bSphere.Center.x) < abs(m_BBox.Center.x) ? bSphere.Center.x : m_BBox.Center.x;
		intersectionBox.Center.y = abs(bSphere.Center.y) < abs(m_BBox.Center.y) ? bSphere.Center.y : m_BBox.Center.y;
		intersectionBox.Center.z = abs(bSphere.Center.z) < abs(m_BBox.Center.z) ? bSphere.Center.z : m_BBox.Center.z;

		intersectionBox.Center.x += xDelta / 2;
		intersectionBox.Center.y += yDelta / 2;
		intersectionBox.Center.z += zDelta / 2;
	}

	return areColliding;
}

bool BoxCollisionComponent::collideWith(BoxCollisionComponent * box_, BoundingBox & intersectionBox)
{
	bool areColliding = false;
	BoundingBox bBox = box_->getBBox();

	if (m_BBox.Intersects(bBox))
	{
		areColliding = true;

		areColliding = true;

		Vector3 combinedRadiuses = Vector3(m_BBox.Extents.x + bBox.Extents.x, m_BBox.Extents.y + bBox.Extents.y, m_BBox.Extents.z + bBox.Extents.z);
		float xDelta = combinedRadiuses.x - abs(m_BBox.Center.x - bBox.Center.x);
		float yDelta = combinedRadiuses.y - abs(m_BBox.Center.y - bBox.Center.y);
		float zDelta = combinedRadiuses.z - abs(m_BBox.Center.z - bBox.Center.z);
		intersectionBox.Extents = Vector3(xDelta, yDelta, zDelta);

		intersectionBox.Center.x = abs(bBox.Center.x) < abs(m_BBox.Center.x) ? bBox.Center.x : m_BBox.Center.x;
		intersectionBox.Center.y = abs(bBox.Center.y) < abs(m_BBox.Center.y) ? bBox.Center.y : m_BBox.Center.y;
		intersectionBox.Center.z = abs(bBox.Center.z) < abs(m_BBox.Center.z) ? bBox.Center.z : m_BBox.Center.z;

		intersectionBox.Center.x += xDelta / 2;
		intersectionBox.Center.y += yDelta / 2;
		intersectionBox.Center.z += zDelta / 2;
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
