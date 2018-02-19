#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <d3d11.h>
#include <SimpleMath.h>

struct Message;
class GameObject;

using namespace DirectX;
using namespace DirectX::SimpleMath;

#define COMPONENT_GRAPHICS 1;
#define COMPONENT_COLLISION 2;
#define COMPONENT_PHYSICS 4;
#define COMPONENT_INPUT 8;
#define COMPONENT_UI 16;

/* Component pattern */

class Component
{
	friend class GameObject;
private:
	GameObject* head;
	size_t type;
public:
	Component(size_t type) : type(type) {}
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Receives a message sent by another component that is connected to the same entity
	*/
	virtual void receive(Message msg) = 0;
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Resets the component
	*/
	virtual void init() = 0;
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleans up any memory the component may be using
	*/
	virtual void cleanup() = 0;
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Updates the component
	*/
	virtual void update() = 0;
	GameObject* getHead() { return this->head; }
	size_t getType() { return this->type; }
};

#endif // !COMPONENT_H
