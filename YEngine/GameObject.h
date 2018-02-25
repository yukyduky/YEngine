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
	GameObject(size_t ID) : ID(ID), pos(Vector3(0.0f, 0.0f, 0.0f)), state(OBJECTSTATE::IDLE), componentTypes(0), parent() {}
	GameObject(size_t ID, Vector3 pos) : ID(ID), pos(pos), state(OBJECTSTATE::IDLE), componentTypes(0), parent() {}

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
	std::list<Component*> components;
	std::unordered_map<size_t, Component*> componentMap;
	GameObject* parent;
	Vector3 pos;
	Vector3 rot;
	Vector3 scale;
	OBJECTSTATE state;
	size_t componentTypes;
	const size_t ID;
};

#endif // !GAMEOBJECT_H
