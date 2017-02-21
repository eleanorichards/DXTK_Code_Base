#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H
//Base Game Object Class
#include "CommonStates.h"
#include "SimpleMath.h"
#include "GameData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Camera;
struct ID3D11DeviceContext;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	//Setters
	void SetPos(Vector3 _pos) { m_pos = _pos; }
	void SetPitch(float _pitch) { m_pitch = _pitch; }
	void SetYaw(float _yaw) { m_yaw = _yaw; }
	void SetRoll(float _roll) { m_roll = _roll; }
	void SetPitchYawRoll(float _pitch, float _yaw, float _roll) { m_pitch = _pitch; m_yaw = _yaw; m_roll = _roll; }
	void SetWorldMat(Matrix _mat) { m_worldMat = _mat; }
	void SetScale(Vector3 _scale) { m_scale = _scale; }
	void SetRadius(float _radius) { m_radius = _radius; };
	virtual void Tick(GameData* _GD);
	void setFudge(Matrix _fudge) { m_fudge = _fudge; }

	float GetRadius() { return m_radius; };
	Vector3 GetPos() { return m_pos; };
	float GetYaw() { return m_yaw; };
	Matrix GetWorldMat() { return m_worldMat; };
	Matrix GetFudge() { return m_fudge; };
	//virtual void Tick(float _dt, unsigned char* _keyboardState);
	virtual void Draw( ID3D11DeviceContext* _pd3dImmediateContext,  CommonStates* _states, Camera* _cam) = 0;


protected:
	Vector3 m_pos;
	float m_radius;
	float m_pitch, m_yaw, m_roll;
	Vector3 m_scale;
	Matrix m_worldMat;
	Matrix m_fudge;
	Matrix  scaleMat;
	Matrix  rotMat;
	Matrix  transMat;

};

#endif