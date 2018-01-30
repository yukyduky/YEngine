#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <DirectXMath.h>

enum class OBJECTSTATE { IDLE, MOVING, DEAD, FROZEN, STOP };

class Component;

using namespace DirectX;

struct Message
{
	OBJECTSTATE state;
	Message(OBJECTSTATE state) : state(state) {}
};

class GameObject
{
public:
	GameObject(const size_t ID) : ID(ID), pos(XMFLOAT3(0.0f, 0.0f, 0.0f)), state(OBJECTSTATE::IDLE) {}
	GameObject(const size_t ID, XMFLOAT3 pos) : ID(ID), pos(pos), state(OBJECTSTATE::IDLE) {}

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Send the parameter 'msg'(obj) to all components that have been added to the object.
	*/
	void send(Message msg);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Adds a component using the 'components.push_back()' function.
	*/
	void addComponent(Component* component);
	void cleanup();
	const size_t getID() const { return this->ID; }
	void setPosition(XMFLOAT3 pos) { this->pos = pos; }
	XMFLOAT3 getPosition() const { return this->pos; }
	void setState(OBJECTSTATE state) { this->state = state; }
	OBJECTSTATE getState() const { return this->state; }
private:
	std::list<Component*> components;
	const size_t ID;
	XMFLOAT3 pos;
	OBJECTSTATE state;
};

#endif // !GAMEOBJECT_H
