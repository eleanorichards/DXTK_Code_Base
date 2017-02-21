#pragma once
#include "camera.h"

class TPSCamera : public Camera
{
public:
	TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance,
		float _farPlaneDistance, GameObject* _target, Vector3 _up, Vector3 _dpos);
	virtual ~TPSCamera();

	virtual void Tick(GameData* _GD) override;

protected:
	GameObject*		m_targetObject;
	Vector3			m_dpos;

};