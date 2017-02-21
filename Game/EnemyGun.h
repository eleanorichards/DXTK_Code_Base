#pragma once

#include "CMOGO.h"
#include "gameobject.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Vehicle.h"
#include <list>

class EnemyGun : public CMOGO
{
public:
	EnemyGun(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Enemy* _parent, string _bulletFileName, int _numBullets, float _pitch, float _yaw, float _roll, Vector3 _scale, Vehicle* _vehicle);
	virtual ~EnemyGun();
	void checkForCollision(GameData* _GD);
	virtual void Tick(GameData* _GD);
	void Draw(ID3D11DeviceContext * _pd3dImmediateContext, CommonStates* _states, Camera* _cam);
	list<Bullet*> m_Bullets;

protected:
	Enemy* m_parent;
	Vehicle* m_vehicle;
};
