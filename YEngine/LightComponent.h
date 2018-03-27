#pragma once
#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include "Component.h"
#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

enum class LIGHT {
	POINT, SPOT, DIRECTIONAL
};

struct LightData
{
	Vector3 position;
	float specPower;
	Vector3 diffuse;
	Vector3 ambient;

	LightData() : position(0.0f, 0.0f, 0.0f), diffuse(0.0f, 0.0f, 0.0f), ambient(0.0f, 0.0f, 0.0f), specPower(0.0f) {}
	LightData(Vector3 position, Vector3 diffuse, Vector3 ambient, float specPower) : position(position), diffuse(diffuse), ambient(ambient), specPower(specPower) {}
};

class LightComponent : public Component
{
protected:
	LIGHT m_Type;
	LightData m_Light;
	bool m_IsPoweredOn;
	float m_Dimmer;
public:
	virtual ~LightComponent() {}

	virtual void init() override;
	virtual void update(float dt) override;
	virtual void cleanup() override;

	LIGHT getType() const;
	bool getIsPoweredOn() const;
	void setIsPoweredOn(bool val);
	LightData getLight() const;
	void setLight(LightData val);
	float getDimmer() const;
	void setDimmer(float val);
};

#endif // LIGHTCOMPONENT_H
