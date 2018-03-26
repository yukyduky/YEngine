#include "PositionalComponent.h"



void PositionalComponent::init()
{
	setPosition(Vector3(0.0f, 0.0f, 0.0f));
}

void PositionalComponent::update(float dt)
{

}

void PositionalComponent::cleanup()
{

}

Vector3 PositionalComponent::getPosition() const
{
	return m_Position;
}

void PositionalComponent::setPosition(Vector3 val)
{
	m_Position = val;
}
