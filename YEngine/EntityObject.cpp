#include "EntityObject.h"



EntityObject::EntityObject(size_t ID) : GameObject(ID)
{
}

void EntityObject::SETvelocity(XMFLOAT3 velocity)
{
	this->velocity = velocity;
}

XMFLOAT3 EntityObject::GETvelocity()
{
	return this->velocity;
}
