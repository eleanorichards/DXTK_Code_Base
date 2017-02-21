#include "EnemyGun.h"

EnemyGun::EnemyGun(string _fileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF, Enemy * _parent, string _bulletFileName, int _numBullets, float _pitch, float _yaw, float _roll, Vector3 _scale, Vehicle* _vehicle) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	GameObject::Tick(nullptr);
	m_fudge;
	m_parent = _parent;
	m_pos = Vector3(0, 0.0f, 0.0f);
	m_pitch = _pitch;
	m_roll = _roll;
	m_yaw = _yaw;
	m_scale = _scale;
	m_vehicle = _vehicle;


	for (int i = 0; i < _numBullets; i++)
	{
		m_Bullets.push_back(new Bullet(_bulletFileName, _pd3dDevice, _EF));
	}
}

EnemyGun::~EnemyGun()
{
}

void EnemyGun::checkForCollision(GameData* _GD)
{
	for (list<Bullet*>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
	{
		if ((*it)->isAlive() && m_vehicle)
		{
			if (_GD->m_CM.CheckForCollision(m_vehicle->GetPos(), (*it)->GetPos()))
			{
				if ((*it)->isAlive())
				{
					(*it)->SetAlive(false);
					m_vehicle->increaseScore();
				}
				
			}
		}
		(*it)->Tick(_GD);
	}
	
}

void EnemyGun::Tick(GameData * _GD)
{
	Vector3 targetPos = m_vehicle->GetPos();
	//Controls to go here
	float rotSpeed = 1.5f * _GD->m_dt;
	//call the base Tick to build out transform relative to the vehicle
	CMOGO::Tick(_GD);
	//m_pos = m_parent->GetPos();

	if (m_parent)
	{
		m_worldMat = m_worldMat * m_parent->GetFudge().Invert() * m_parent->GetWorldMat();
	}

	if (_GD->m_dt * 0.1 > ((float)rand() / (float)RAND_MAX))
	{
		for (list<Bullet*>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
		{
			if (!(*it)->isAlive())
			{				
				//calculate direction and location of fired bullet
				Vector3 bulletPos = Vector3::Transform(Vector3(-7.0f, 0.0f, 0.0f), m_fudge.Invert() * m_worldMat);
				Vector3 bulletDir = targetPos - bulletPos;
				Vector3 bulletUp = Vector3::Transform(Vector3::One, m_fudge.Invert() * m_worldMat) - bulletPos;
				//see below
				bulletDir.Normalize();
				bulletUp.Normalize();
				(*it)->Spawn(5.0f, bulletPos, bulletDir, bulletUp, 0.01*Vector3::One, 50.0f);
				break;
			}
		}
	}
	for (list<Bullet *>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
	{
		(*it)->Tick(_GD);
	}
	checkForCollision(_GD);
}

void EnemyGun::Draw(ID3D11DeviceContext * _pd3dImmediateContext, CommonStates * _states, Camera * _cam)
{
	if (m_parent->isAlive())
	{
		CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
		//draw all objects
		for (list<Bullet *>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
		{
			(*it)->Draw(_pd3dImmediateContext, _states, _cam);
		}
	}
	else
	{
		for (list<Bullet *>::iterator it = m_Bullets.begin(); it != m_Bullets.end(); it++)
		{
			(*it)->SetAlive(false);
		}
	}
}
