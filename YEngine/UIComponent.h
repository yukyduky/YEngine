#pragma once
#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "Component.h"

class UIComponent : public Component
{
public:
	virtual void receive(Message msg);
	virtual void init();
	virtual void cleanup();	
	virtual void update();
};

#endif // !UICOMPONENT_H
