#include "Gun.h"



Gun::Gun(string _fileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF, GameObject * _parent, string _bulletFileName, int _numBullets, float _pitch, float _yaw, float _roll, Vector3 _scale) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	GameObject::Tick(nullptr);
	m_fudge;
	m_parent = _parent;
	m_pos = Vector3(-140.0f, 70.0f, 0.0f);
	m_pitch = _pitch;
	m_roll = _roll;
	m_yaw = _yaw;
	m_scale = _scale;
	

	for (int i = 0; i < _numBullets; i++)
	{
		m_Bullets.push_back(new Bullet(_bulletFileName, _pd3dDevice, _EF));
	}
}

Gun::~Gun()
{

}

void Gun::Tick(GameData * _GD)
{
	//Controls to go here
	float rotSpeed = 1.5f * _GD->m_dt;
	//call the base Tick to build out transform relative to the vehicle
	CMOGO::Tick(_GD);
	//m_pos = m_parent->GetPos();
	
	if (m_parent)
	{
		m_worldMat = m_worldMat * m_parent->GetFudge().Invert() * m_parent->GetWorldMat();
	}

	if ((_GD->m_keyboardState[DIK_SPACE] & 0x80) && !(_GD->m_prevKeyboardState[DIK_SPACE]))
	{
		for (list<Bullet*>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
		{
			if (!(*it)->isAlive())
			{
				Vector3 bulletPos = Vector3::Transform(Vector3(-7.0f, 0.0f, 0.0f), m_fudge.Invert() * m_worldMat);
				Vector3 bulletDir = Vector3::Transform(Vector3::Forward, m_fudge.Invert() * m_worldMat) - bulletPos;
				Vector3 bulletUp = Vector3::Transform(Vector3::One, m_fudge.Invert() * m_worldMat) - bulletPos;
				//calculate direction and location of fired bullet
				//see below
				bulletDir.Normalize();
				bulletUp.Normalize();
				(*it)->Spawn(3.0f, bulletPos, bulletDir, bulletUp, 0.01*Vector3::One, 50.0f);
				break;
			}
		}
	}
	for (list<Bullet *>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
	{
		(*it)->Tick(_GD);
	}
	
	switch (_GD->m_GS)
	{
	case GS_PLAY_MAIN_CAM:
		//Keyboard control of the GUN
		//left arrow
		if (_GD->m_keyboardState[DIK_LEFTARROW] & 0x80)
		{
			//adjust vector forward left
			m_yaw += rotSpeed;
		}
		//right arrow
		if (_GD->m_keyboardState[DIK_RIGHTARROW] & 0x80)
		{
			//adjust vector forward right
			m_yaw -= rotSpeed;
		}
		//up arrow
		if (_GD->m_keyboardState[DIK_UPARROW] & 0x80)
		{
			m_roll -= rotSpeed;
		}
		//down arrow
		if (_GD->m_keyboardState[DIK_DOWNARROW] & 0x80)
		{
			//std::cout << m_pos;
			m_roll += rotSpeed;
		}
		break;
	case GS_PLAY_TPS_CAM:
		//mouse control of the GUN
		m_yaw -= (0.1*rotSpeed) * _GD->m_mouseState->lX;
		break;
	}
	//bounds checks for gun rotation
	if (m_roll > XM_PIDIV4)
		m_roll = XM_PIDIV4;
	if (m_roll < -XM_PIDIV4)
		m_roll = -XM_PIDIV4;
	if(m_yaw < -XM_PIDIV4 - 2)
		m_yaw = -XM_PIDIV4 - 2;
	if (m_yaw > XM_PIDIV4 - 2)
		m_yaw = XM_PIDIV4 - 2;
}

void Gun::Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam)
{
	CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
	//draw all objects
	for (list<Bullet *>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
	{
		(*it)->Draw(_pd3dImmediateContext, _states, _cam);
	}
};
