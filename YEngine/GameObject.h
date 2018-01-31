#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <SimpleMath.h>

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
	GameObject() : pos(Vector3(0.0f, 0.0f, 0.0f)), state(OBJECTSTATE::IDLE) {}
	GameObject(Vector3 pos) : pos(pos), state(OBJECTSTATE::IDLE) {}

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Send the parameter 'msg'(obj) to all components that have been added to the object.
	*/
	void send(Message msg);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Adds a component using the 'components.push_back()' function.
	*/
	void addComponent(Component* component);
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
private:
	std::list<Component*> components;
	Vector3 pos;
	Vector3 rot;
	Vector3 scale;
	OBJECTSTATE state;
};

#endif // !GAMEOBJECT_H
