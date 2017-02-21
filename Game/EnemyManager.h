#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_
#include "gameobject.h"
#include <list>
#include "Model.h"
#include <string>
#include "Enemy.h"
#include "Bullet.h"
#include "CollisionManager.h"

using namespace std;
using namespace DirectX;

class Enemy;
class Bullet;
class Gun;

class EnemyManager : public GameObject
{
public:
	EnemyManager(int _numEnemies, string _enemyFileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Gun* _gun);
	~EnemyManager();
	void checkForCollisions(GameData* _GD);
	void increaseEnemyScore();
	virtual void Tick(GameData* _GD) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;
	int getEnemyScore();
	list<Enemy*> GetEnemy();

protected:
	list<Enemy*> m_Enemies;
	list<Bullet*> player_Bullets;
	Vector3 initialLocation;
	Vector3 travelDirection;
	int max = 100;
	int min = -400;
	int enemyScore = 0;
};

#endif
