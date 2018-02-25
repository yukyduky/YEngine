#include "GameObject.h"
#include "Component.h"
#include "Locator.h"


void GameObject::send(Message msg)
{
	// Send the message to all the components that have been added to the object
	for (auto &i : this->components) 
	{
		i->receive(msg);
	}
}

void GameObject::addComponent(Component* component, size_t type)
{
	this->components.push_back(component);
	this->components.back()->head = this;
	this->components.back()->type = type;
	this->componentMap[type] = component;
	this->componentTypes |= type;
}

void GameObject::update()
{
	for (auto &i : this->components) 
	{
		i->update();
	}
}

void GameObject::cleanup()
{
	for (auto &i : this->components) 
	{
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
	if (state == OBJECTSTATE::DEAD) 
	{
		Locator::getEventHandler()->addEvent(Event(EVENT::OBJECTDIED, this->ID));
	}
}

OBJECTSTATE GameObject::getState()
{
	return this->state;
}

size_t GameObject::getComponentTypes()
{
	return this->componentTypes;
}

Component* GameObject::getComponent(size_t type)
{
	Component* component = nullptr;
	if ((this->componentTypes & type) == type) 
	{
		component = this->componentMap[type];
	}
	return component;
}
