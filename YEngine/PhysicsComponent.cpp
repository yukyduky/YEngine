#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Locator.h"

void PhysicsComponent::receive(Message msg)
{
}

void PhysicsComponent::init()
{
	this->acceleration = Vector3(0.0f, 0.0f, 0.0f);
	this->velocity = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsComponent::cleanup()
{
}

void PhysicsComponent::update()
{
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->velocity += this->acceleration * dt;
	this->getHead()->move(this->velocity * dt);
}

void PhysicsComponent::setup(float weight)
{
	this->weight = weight;

	this->init();
}

void PhysicsComponent::setVeloctiy(Vector3 velocity)
{
	this->velocity = velocity;
}

Vector3 PhysicsComponent::getVelocity()
{
	return this->velocity;
}

void PhysicsComponent::setAcceleration(Vector3 acceleration)
{
	this->acceleration = acceleration;
}

Vector3 PhysicsComponent::getAcceleration()
{
	return this->acceleration;
}
