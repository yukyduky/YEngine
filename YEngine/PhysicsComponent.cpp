#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Locator.h"

void PhysicsComponent::receive(Message msg)
{
}

void PhysicsComponent::init()
{
	m_Acceleration = Vector3(0.0f, 0.0f, 0.0f);
	m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsComponent::cleanup()
{
}

void PhysicsComponent::update()
{
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	m_Velocity += m_Acceleration * dt;
	this->getHead()->move(m_Velocity * dt);
}

void PhysicsComponent::setup(float weight)
{
	m_Weight = weight;

	this->init();
}

void PhysicsComponent::setVeloctiy(Vector3 velocity)
{
	m_Velocity = velocity;
}

Vector3 PhysicsComponent::getVelocity()
{
	return m_Velocity;
}

void PhysicsComponent::setAcceleration(Vector3 acceleration)
{
	m_Acceleration = acceleration;
}

Vector3 PhysicsComponent::getAcceleration()
{
	return m_Acceleration;
}
