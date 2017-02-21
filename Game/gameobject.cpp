#include "gameobject.h"

GameObject::GameObject()
{
	//set the Gameobject to the origin with no rotation and unit scaling 
	m_pos = Vector3::Zero;
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_scale = Vector3::One;
	Matrix m_fudge;
	m_worldMat = Matrix::Identity;
	m_fudge = Matrix::Identity;
	m_radius = 10.0f;
}

GameObject::~GameObject()
{

}

void GameObject::Tick(GameData* _GD)
{
	//build up the world matrix depending on the new position of the GameObject
	//the assumption is that this class will be inherited by the class that ACTUALLY changes this
	scaleMat	= Matrix::CreateScale(m_scale);
	rotMat		= Matrix::CreateFromYawPitchRoll( m_yaw, m_pitch, m_roll ); 
	transMat	= Matrix::CreateTranslation(m_pos);
	m_worldMat = m_fudge * scaleMat * rotMat * transMat;
	m_worldMat = scaleMat * rotMat * transMat;
}