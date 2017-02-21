#include "Enemy.h"

Enemy::Enemy(string _fileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	m_alive = false;
	m_fudge = Matrix::Identity;

}

Enemy::~Enemy()
{
}

void Enemy::Spawn(Vector3 pos, Vector3 _scale, Vector3 _dir, Vector3 _up)
{
	m_alive = true; // turn this enemy ON
	m_pos = pos;//origin
	m_scale = _scale;//scale
	m_dir = _dir;//direction
	m_up = _up;//orientation
	//travelDirection = Vector3(((rand() % max - min) + min), 0.0f, ((rand() % max - min) + min));
}

void Enemy::Tick(GameData * _GD)
{
	if (m_alive)
	{
		//set random travel direction
		if (_GD->m_dt * 0.5 > ((float)rand() / (float)RAND_MAX))
		{
			travelDirection = Vector3(((float)(rand() % max) - min), 0.0f, (((float)(rand() % max) - min)));
		}
		//do all your enemy things (AI etc)
		m_pos += travelDirection * _GD->m_dt;
		
		Matrix scaleMat = Matrix::CreateScale(m_scale);
		m_worldMat = m_fudge * scaleMat;
		CMOGO::Tick(_GD);
		//set boundaries of map
		if (m_pos.x >= 400)
		{
			travelDirection = Vector3(((float)(rand() % max) - min), 0.0f, (((float)(rand() % max) - min)));
		}
		if (m_pos.x <= -300)
		{
			travelDirection = Vector3(((float)(rand() % max) - min), 0.0f, (((float)(rand() % max) - min)));
		}
		if (m_pos.y >= 400)
		{
			travelDirection = Vector3(((float)(rand() % max) - min), 0.0f, (((float)(rand() % max) - min)));
		}
		if (m_pos.y <= -200)
		{
			travelDirection = Vector3(((float)(rand() % max) - min), 0.0f, (((float)(rand() % max) - min)));
		}

	}


}

void Enemy::Draw(ID3D11DeviceContext * _pd3dImmediateContext, CommonStates * _states, Camera * _cam)
{
	if (m_alive)
	{
		CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
	}
}



void Enemy::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}

