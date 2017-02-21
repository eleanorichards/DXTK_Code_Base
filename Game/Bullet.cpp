#include "Bullet.h"
#include "GameData.h"

Bullet::Bullet(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) :CMOGO( _fileName, _pd3dDevice, _EF)
{

	m_alive = false;
	m_lifeLeft = 0.0f;
	m_fudge = Matrix::Identity;
}

Bullet::~Bullet()
{

}

void Bullet::Spawn(float _life, Vector3 _pos, Vector3 _dir, Vector3 _up, Vector3 _scale, float _radius)
{
	m_alive = true; // turn this bullet on
	m_lifeLeft = _life; //restrain it's life to a few seconds
	m_pos = _pos;//origin
	m_dir = _dir;//direction
	m_up = _up;//orientation
	m_scale = _scale; //scale
	m_radius = _radius; //radius for collision
}

void Bullet::Tick(GameData * _GD)
{

	if (m_alive)
	{
		m_lifeLeft -= _GD->m_dt;
		if (m_lifeLeft <= 0.0f)
		{
			m_alive = false;
			return;
		}
		float speed = 150.0f;
		m_pos += speed * _GD->m_dt * m_dir;
		Matrix scaleMat = Matrix::CreateScale(m_scale);
		Matrix rotTransMat = Matrix::CreateWorld(m_pos, m_dir, m_up);

		m_worldMat = m_fudge * scaleMat * rotTransMat;
		CMOGO::Tick(_GD);
	}

}

void Bullet::Draw(ID3D11DeviceContext * _pd3dImmediateContext, CommonStates * _states, Camera * _cam)
{
	if (m_alive)
	{
		CMOGO::Draw(_pd3dImmediateContext, _states, _cam);
	}
}

void Bullet::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}

