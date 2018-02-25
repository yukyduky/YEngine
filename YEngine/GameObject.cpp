#include "GameObject.h"
#include "Component.h"
#include "Locator.h"


GameObject::GameObject(size_t ID) : m_ID(ID), m_Pos(Vector3(0.0f, 0.0f, 0.0f)), m_ComponentTypes(0), m_State(OBJECTSTATE::IDLE), m_Parent()
{
}

GameObject::GameObject(size_t ID, Vector3 pos) : m_ID(ID), m_Pos(pos), m_ComponentTypes(0), m_State(OBJECTSTATE::IDLE), m_Parent()
{
}

void GameObject::send(Message msg)
{
	// Send the message to all the components that have been added to the object
	for (auto &i : m_Components) 
	{
		i->receive(msg);
	}
}

void GameObject::addComponent(Component* component, size_t type)
{
	m_Components.push_back(component);
	m_Components.back()->m_Head = this;
	m_Components.back()->m_Type = type;
	m_ComponentMap[type] = component;
	m_ComponentTypes |= type;
}

void GameObject::update()
{
	for (auto &i : m_Components) 
	{
		i->update();
	}
}

void GameObject::cleanup()
{
	for (auto &i : m_Components) 
	{
		i->cleanup();
	}
}

void GameObject::move(Vector3 offset)
{
	m_Pos += offset;
}

void GameObject::setPosition(Vector3 pos)
{
	m_Pos = pos;
}

Vector3 GameObject::getPosition()
{
	return m_Pos;
}

void GameObject::setRotation(Vector3 rot)
{
	m_Rot = rot;
}

Vector3 GameObject::getRotation()
{
	return m_Rot;
}

void GameObject::setScale(Vector3 scale)
{
	m_Scale = scale;
}

Vector3 GameObject::getScale()
{
	return m_Scale;
}

void GameObject::setState(OBJECTSTATE state)
{
	m_State = state;
	if (state == OBJECTSTATE::DEAD) 
	{
		Locator::getEventHandler()->addEvent(Event(EVENT::OBJECTDIED, m_ID));
	}
}

OBJECTSTATE GameObject::getState()
{
	return m_State;
}

size_t GameObject::getComponentTypes()
{
	return m_ComponentTypes;
}

Component* GameObject::getComponent(size_t type)
{
	Component* component = nullptr;
	if ((m_ComponentTypes & type) == type) 
	{
		component = m_ComponentMap[type];
	}
	return component;
}
