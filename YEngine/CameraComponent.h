#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"

class CameraComponent :	public Component
{
protected:
	Matrix m_View;
	Matrix m_Projection;

	Vector3 m_UpVector;
	Vector3 m_RightVector;
	Vector3 m_ForwardVector;
	Vector3 m_Position;

	float m_FieldOfView;
	float m_FarPlane;
	float m_NearPlane;
	float m_AspectRatio;
public:
	CameraComponent();
	virtual ~CameraComponent() {}

	virtual void init();
	virtual void update(float dt);
	virtual void cleanup();

	void rebuildAll();
	void rebuildView();
	void rebuildProjection();

	Matrix& getViewMatrix();
	Matrix& getProjectionMatrix();

	Vector3 getUpVector() const;
	void setUpVector(Vector3 val);
	Vector3 getRightVector() const;
	void setRightVector(Vector3 val);
	Vector3 getForwardVector() const;
	void setForwardVector(Vector3 val);
	Vector3 getPosition() const;
	void setPosition(Vector3 val);
	float getFieldOfView() const;
	void setFieldOfView(float val);
	float getFarPlane() const;
	void setFarPlane(float val);
	float getNearPlane() const;
	void setNearPlane(float val);
	float getAspectRatio() const;
	void setAspectRatio(float val);
};

#endif // CAMERACOMPONENT_H
