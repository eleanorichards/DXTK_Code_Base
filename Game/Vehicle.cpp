#include "Vehicle.h"
#include <dinput.h>
#include <iostream>
//Vehicle::Vehicle(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
	//any special set up for Vehicle goes here

Vehicle::Vehicle(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll, Vector3 _scale , float _radius) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	m_pos = _pos;
	m_pitch = _pitch;
	m_roll = _roll;
	m_yaw = _yaw;
	m_scale = _scale;
	m_radius = _radius;
	GameObject::Tick(nullptr); //updte my world_transform
	forwards = Vector3(0.0f, 0.0f, 1.0f);
	//m_roll -= 20;
	m_pitch += 0;
	
}

Vehicle::~Vehicle()
{
	//tidy up anything I've created
}

int Vehicle::getPlayerScore()
{
	return playerScore;
}


void Vehicle::increaseScore()
{
	playerScore += 10;
}



Vector3 Vehicle::GetPos()
{
	 return m_pos; 
}

void Vehicle::Tick(GameData* _GD)
{
	float rotSpeed = 2.0f * _GD->m_dt;

	//Keyboard control of the Vehicle
	//left arrow
	if (_GD->m_keyboardState[DIK_A] & 0x80)
	{
		//adjust vector forward left
		m_yaw += rotSpeed;
	}
	//right arrow
	if (_GD->m_keyboardState[DIK_D] & 0x80)
	{
		//adjust vector forward right
		m_yaw -= rotSpeed;
	}
	//up arrow
	if (_GD->m_keyboardState[DIK_W] & 0x80)
	{
		m_pos += Vector3::Transform(forwards, rotMat);
	}
	//down arrow
	if (_GD->m_keyboardState[DIK_S] & 0x80)
	{
		//std::cout << m_pos;
		m_pos -= Vector3::Transform(forwards, rotMat);

	}
	
	switch (_GD->m_GS)
	{
	case GS_PLAY_MAIN_CAM:
		//mouse control
		/*m_pos.x += 0.01f * _GD->m_mouseState->lX;
		m_pos.z += 0.01f * _GD->m_mouseState->lY;*/
		break;
	case GS_PLAY_TPS_CAM:
		
		//turn and forward controls
		break;
	}
	//checkForCollisions(_GD);
	//apply my base behaviour
	CMOGO::Tick(_GD);
}

void Vehicle::Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam)
{
	//I'm still a CMOGO so that's what draws me
	CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
}