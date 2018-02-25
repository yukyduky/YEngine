#include "GraphicsComponent.h"
#include "GameObject.h"

void GraphicsComponent::receive(Message msg)
{
}

void GraphicsComponent::init()
{
	m_World = Matrix::CreateWorld(this->getHead()->getPosition(), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));
}

void GraphicsComponent::cleanup()
{
}

void GraphicsComponent::update()
{
	m_World.Translation(this->getHead()->getPosition());
	Vector3 rot = this->getHead()->getPosition();
	m_World *= Matrix::CreateFromYawPitchRoll(rot.x, rot.y, rot.z) * Matrix::CreateScale(this->getHead()->getScale());
}
