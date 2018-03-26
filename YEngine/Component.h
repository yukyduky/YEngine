#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
	virtual ~Component() {}

	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void cleanup() = 0;
};

#endif // !COMPONENT_H
