#ifndef _GUN_H_
#define _GUN_H_
#include "CMOGO.h"
#include "gameobject.h"
#include "Bullet.h"
#include <list>

class Gun : public CMOGO
{
public:
	Gun(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, GameObject* _parent, string _bulletFileName, int _numBullets, float _pitch, float _yaw, float _roll, Vector3 _scale);
	virtual ~Gun();

	virtual void Tick(GameData* _GD);
	void Draw(ID3D11DeviceContext * _pd3dImmediateContext , CommonStates* _states, Camera* _cam);
	list<Bullet*> m_Bullets;

protected:
	GameObject* m_parent;
};
#endif