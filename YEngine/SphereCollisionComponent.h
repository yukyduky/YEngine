#pragma once
#ifndef SPHERECOLLISIONCOMPONENT_H
#define SPHERECOLLISIONCOMPONENT_H

#include "CollisionComponent.h"

class BoxCollisionComponent;

class SphereCollisionComponent : public CollisionComponent
{
private:
	BoundingSphere m_BSphere;
public:
	SphereCollisionComponent();
	virtual ~SphereCollisionComponent() {}

	void init() override;
	void update(float dt) override;
	void cleanup() override;

	bool collideWith(CollisionComponent* collision_, BoundingBox& intersectionBox) override;
	bool collideWith(SphereCollisionComponent* sphere_, BoundingBox& intersectionBox) override;
	bool collideWith(BoxCollisionComponent* box_, BoundingBox& intersectionBox) override;

	void setPosition(Vector3 val) override;
	void setRadius(Vector3 val) override;

	BoundingSphere getBSphere() const;
	void setBSphere(BoundingSphere val);
};

#endif // SPHERECOLLISIONCOMPONENT_H
