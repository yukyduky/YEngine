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
	virtual void receive(Message msg) = 0;
	virtual void init() = 0;
	virtual void cleanup() = 0;
	virtual void update() = 0;
	GameObject* getHead() { return this->head; }
};

#endif // !COMPONENT_H
