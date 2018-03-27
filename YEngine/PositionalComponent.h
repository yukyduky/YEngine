#pragma once
#ifndef POSITIONALCOMPONENT_H
#define POSITIONALCOMPONENT_H

#include "Component.h"

class PositionalComponent : public Component
{
private:
	Vector3 m_Position;
public:
	PositionalComponent();
	virtual ~PositionalComponent() {}

	virtual void init() override;
	virtual void update(float dt) override;
	virtual void cleanup() override;

	Vector3 getPosition() const;
	void setPosition(Vector3 val);
};

#endif // POSITIONALCOMPONENT_H
