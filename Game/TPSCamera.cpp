#include "TPSCamera.h"
#include "gameobject.h"


TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance,
	float _farPlaneDistance, GameObject* _target, Vector3 _up, Vector3 _dpos)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance,
		_target->GetPos(), _up)
{
	m_targetObject = _target;
	m_dpos = _dpos;
}
TPSCamera::~TPSCamera()
{
}

void TPSCamera::Tick(GameData* _GD)
{
	//set up camera and target position based on new pos and orientation of target
	//something like setting dpos Vector3::Transform(forwards, rotMat)
	m_target = m_targetObject->GetPos();
	Matrix rotMat = Matrix::CreateRotationY(m_targetObject->GetYaw());

	m_pos = m_target + Vector3::Transform(m_dpos, rotMat);
	//then set up proj and view matrices

	Camera::Tick(_GD);
}