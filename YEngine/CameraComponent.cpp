#include "CameraComponent.h"


CameraComponent::CameraComponent()
{
	m_Position = Vector3(0.0f, 0.0f, 0.0f);
	m_UpVector = Vector3(0.0f, 1.0f, 0.0f);
	m_RightVector = Vector3(1.0f, 0.0f, 0.0f);
	m_ForwardVector = Vector3(0.0f, 0.0f, 1.0f);

	m_FieldOfView = 45.0f;
	m_FarPlane = 1000.0f;
	m_NearPlane = 1.0f;
	m_AspectRatio = 1920 / 1080;
}

void CameraComponent::init()
{
	this->rebuildAll();
}

void CameraComponent::update(float dt)
{

}

void CameraComponent::cleanup()
{

}

void CameraComponent::rebuildAll()
{
	this->rebuildView();
	this->rebuildProjection();
}

void CameraComponent::rebuildView()
{
	m_View = DirectX::XMMatrixLookToLH(m_Position, m_ForwardVector, m_UpVector);
}

void CameraComponent::rebuildProjection()
{
	m_Projection = DirectX::XMMatrixPerspectiveFovLH(m_FieldOfView, m_AspectRatio, m_NearPlane, m_FarPlane);
}

Matrix& CameraComponent::getViewMatrix()
{
	return m_View;
}

Matrix& CameraComponent::getProjectionMatrix()
{
	return m_Projection;
}

Vector3 CameraComponent::getUpVector() const
{
	return m_UpVector;
}

void CameraComponent::setUpVector(Vector3 val)
{
	m_UpVector = val;
}

Vector3 CameraComponent::getRightVector() const
{
	return m_RightVector;
}

void CameraComponent::setRightVector(Vector3 val)
{
	m_RightVector = val;
}

Vector3 CameraComponent::getForwardVector() const
{
	return m_ForwardVector;
}

void CameraComponent::setForwardVector(Vector3 val)
{
	m_ForwardVector = val;
}

Vector3 CameraComponent::getPosition() const
{
	return m_Position;
}

void CameraComponent::setPosition(Vector3 val)
{
	m_Position = val;
}

float CameraComponent::getFieldOfView() const
{
	return m_FieldOfView;
}

void CameraComponent::setFieldOfView(float val)
{
	m_FieldOfView = val;
}

float CameraComponent::getFarPlane() const
{
	return m_FarPlane;
}

void CameraComponent::setFarPlane(float val)
{
	m_FarPlane = val;
}

float CameraComponent::getNearPlane() const
{
	return m_NearPlane;
}

void CameraComponent::setNearPlane(float val)
{
	m_NearPlane = val;
}

float CameraComponent::getAspectRatio() const
{
	return m_AspectRatio;
}

void CameraComponent::setAspectRatio(float val)
{
	m_AspectRatio = val;
}