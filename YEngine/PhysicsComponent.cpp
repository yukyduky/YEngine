#include "PhysicsComponent.h"

void PhysicsComponent::init()
{
	m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
	m_Acceleration = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsComponent::update(float dt)
{
	m_Velocity += m_Acceleration * dt;
}

void PhysicsComponent::cleanup()
{
}

Vector3 PhysicsComponent::getVelocity() const
{
	return m_Velocity;
}

void PhysicsComponent::setVelocity(Vector3 val)
{
	m_Velocity = val;
}

Vector3 PhysicsComponent::getAcceleration() const
{
	return m_Acceleration;
}

void PhysicsComponent::setAcceleration(Vector3 val)
{
	m_Acceleration = val;
}