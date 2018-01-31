#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <d3d11.h>
#include <SimpleMath.h>

struct Message;
class GameObject;

using namespace DirectX;
using namespace DirectX::SimpleMath;

/* Component pattern */

class Component
{
	friend class GameObject;
private:
	GameObject* head;
public:
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
};

#endif // !COMPONENT_H
