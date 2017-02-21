#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"CMOGO.h"

class Enemy : public CMOGO
{
public:
	Enemy(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Enemy();

	void Spawn(Vector3 pos, Vector3 _scale, Vector3 _dir, Vector3 _up);
	virtual void Tick(GameData* _GD) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;

	void SetAlive(bool isAlive);

	bool isAlive() { return m_alive; }

protected:
	bool m_alive; // is this enemy alive
	Vector3 m_target; // I am travelling towards this location
	Vector3 m_dir;
	Vector3 m_up;
	Vector3 travelDirection;
	int max = 100;
	int min = 50;
	int enemyScore = 0;
};

#endif