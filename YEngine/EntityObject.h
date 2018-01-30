#pragma once
#ifndef ENTITYOBJECT_H
#define ENTITYOBJECT_H

#include "GameObject.h"

class EntityObject : public GameObject
{
private:
	XMFLOAT3 velocity;
public:
	EntityObject(size_t ID);
	void SETvelocity(XMFLOAT3 velocity);
	XMFLOAT3 GETvelocity();
};

#endif // !ENTITYOBJECT_H
