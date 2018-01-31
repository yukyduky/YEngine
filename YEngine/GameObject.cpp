#include "GameObject.h"
#include "Component.h"


void GameObject::send(Message msg)
{
	// Send the message to all the components that have been added to the object
	for (auto &i : this->components) {
		i->receive(msg);
	}
}

void GameObject::addComponent(Component* component)
{
	this->components.push_back(component);
	this->components.back()->head = this;
}

void GameObject::update()
{
	for (auto &i : this->components) {
		i->update();
	}
}

void GameObject::cleanup()
{
	// Cleanup all the components
	for (auto &i : this->components) {
		i->cleanup();
	}
}

void GameObject::move(Vector3 offset)
{
	this->pos += offset;
}

void GameObject::setPosition(Vector3 pos)
{
	this->pos = pos;
}

Vector3 GameObject::getPosition()
{
	return this->pos;
}

void GameObject::setRotation(Vector3 rot)
{
	this->rot = rot;
}

Vector3 GameObject::getRotation()
{
	return this->rot;
}

void GameObject::setScale(Vector3 scale)
{
	this->scale = scale;
}

Vector3 GameObject::getScale()
{
	return this->scale;
}

void GameObject::setState(OBJECTSTATE state)
{
	this->state = state;
}

OBJECTSTATE GameObject::getState()
{
	return this->state;
}
