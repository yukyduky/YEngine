#pragma once
#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXCollision.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

class SphereCollisionComponent;
class BoxCollisionComponent;

class CollisionComponent : public Component
{
public:
	virtual ~CollisionComponent() {}

	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void cleanup() = 0;

	virtual bool collideWith(CollisionComponent* collision_, BoundingBox& intersectionBox) = 0;
	virtual bool collideWith(SphereCollisionComponent* sphere_, BoundingBox& intersectionBox) = 0;
	virtual bool collideWith(BoxCollisionComponent* box_, BoundingBox& intersectionBox) = 0;

	virtual void setPosition(Vector3 val) = 0;
	virtual void setRadius(Vector3 val) = 0;
};

#endif // COLLISIONCOMPONENT_H
