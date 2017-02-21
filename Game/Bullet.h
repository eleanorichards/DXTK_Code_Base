#ifndef _BULLET_H_
#define _BULLET_H_
#include "CMOGO.h"
#include "CollisionManager.h"


//class Enemy 

class Bullet : public CMOGO
{
public:
	Bullet(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Bullet();

	void Spawn(float _life, Vector3 _pos, Vector3 _dir, Vector3 _up, Vector3 _scale, float _radius);

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;

	void SetAlive(bool isAlive);
	bool isAlive() { return m_alive; }

protected:
	
	bool m_alive;
	float m_lifeLeft;
	Vector3 m_dir;
	Vector3 m_up;
};

#endif