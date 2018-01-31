#include "GraphicsComponent.h"
#include "GameObject.h"

void GraphicsComponent::receive(Message msg)
{
}

void GraphicsComponent::init()
{
	this->world = Matrix::CreateWorld(this->getHead()->getPosition(), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));
}

void GraphicsComponent::cleanup()
{
}

void GraphicsComponent::update()
{
	this->world.Translation(this->getHead()->getPosition());
	Vector3 rot = this->getHead()->getPosition();
	this->world *= Matrix::CreateFromYawPitchRoll(rot.x, rot.y, rot.z) * Matrix::CreateScale(this->getHead()->getScale());
}

void GraphicsComponent::setup(RESOURCEID resourceID)
{
	this->resourceID = resourceID;

	this->init();
}

RESOURCEID GraphicsComponent::getResourceID()
{
	return this->resourceID;
}
