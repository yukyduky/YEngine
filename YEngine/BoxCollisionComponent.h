#pragma once
#ifndef BOXCOLLISIONCOMPONENT_H
#define BOXCOLLISIONCOMPONENT_H

#include "CollisionComponent.h"

class SphereCollisionComponent;

class BoxCollisionComponent : public CollisionComponent
{
private:
	BoundingBox m_BBox;
public:
	virtual ~BoxCollisionComponent() {}

	void init() override;
	void update() override;
	void cleanup() override;

	bool collideWith(CollisionComponent* collision_, BoundingBox& intersectionBox) override;
	bool collideWith(SphereCollisionComponent* sphere_, BoundingBox& intersectionBox) override;
	bool collideWith(BoxCollisionComponent* box_, BoundingBox& intersectionBox) override;

	void setPosition(Vector3 val) override;
	void setRadius(Vector3 val) override;

	BoundingBox getBBox() const;
	void setBBox(BoundingBox val);
};

#endif // BOXCOLLISIONCOMPONENT_H
