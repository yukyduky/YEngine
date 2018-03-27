#include "LightComponent.h"



void LightComponent::init()
{
	m_IsPoweredOn = true;
	m_Dimmer = 0.0f;
}

void LightComponent::update(float dt)
{
	m_Light.diffuse *= 1.0f + m_Dimmer * dt;
	m_Light.ambient *= 1.0f + m_Dimmer * dt;
}

void LightComponent::cleanup()
{
}

LIGHT LightComponent::getType() const
{
	return m_Type;
}

bool LightComponent::getIsPoweredOn() const
{
	return m_IsPoweredOn;
}

void LightComponent::setIsPoweredOn(bool val)
{
	m_IsPoweredOn = val;
}

LightData LightComponent::getLight() const
{
	return m_Light;
}

void LightComponent::setLight(LightData val)
{
	m_Light = val;
}

float LightComponent::getDimmer() const
{
	return m_Dimmer;
}

void LightComponent::setDimmer(float val)
{
	m_Dimmer = val;
}