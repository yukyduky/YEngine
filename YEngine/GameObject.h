#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <SimpleMath.h>
#include <unordered_map>

enum class OBJECTSTATE { IDLE, MOVING, DEAD, FROZEN, STOP };

class Component;

using namespace DirectX;
using namespace DirectX::SimpleMath;

struct Message
{
	OBJECTSTATE state;
	Message(OBJECTSTATE state) : state(state) {}
};

class GameObject
{
public:
	GameObject(size_t ID);
	GameObject(size_t ID, Vector3 pos);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Send the parameter 'msg'(obj) to all components that have been added to the object.
	*/
	void send(Message msg);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Adds a component using the 'components.push_back()' function.
	*/
	void addComponent(Component* component, size_t type);
	void update();
	void cleanup();

	void move(Vector3 offset);

	void setPosition(Vector3 pos);
	Vector3 getPosition();
	void setRotation(Vector3 rot);
	Vector3 getRotation();
	void setScale(Vector3 scale);
	Vector3 getScale();
	void setState(OBJECTSTATE state);
	OBJECTSTATE getState();
	size_t getComponentTypes();
	Component* getComponent(size_t type);
private:
	std::list<Component*> m_Components;
	std::unordered_map<size_t, Component*> m_ComponentMap;
	GameObject* m_Parent;
	Vector3 m_Pos;
	Vector3 m_Rot;
	Vector3 m_Scale;
	OBJECTSTATE m_State;
	size_t m_ComponentTypes;
	const size_t m_ID;
};

#endif // !GAMEOBJECT_H
