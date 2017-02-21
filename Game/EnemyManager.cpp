#include "EnemyManager.h"
#include "Gun.h"
#include "CollisionManager.h"

EnemyManager::EnemyManager(int _numEnemies, string _enemyFileName, ID3D11Device * _pd3dDevice, IEffectFactory * _EF, Gun* _gun)
{
	for (int i = 0; i < _numEnemies; i++)
	{
		m_Enemies.push_back(new Enemy(_enemyFileName, _pd3dDevice, _EF));
	}
	player_Bullets = _gun->m_Bullets;
	initialLocation = Vector3(-280.0f, 0.0f, -100.0f);
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Tick(GameData * _GD)
{

	if (_GD->m_dt * 0.2 > ((float)rand() / (float)RAND_MAX))
	{
		for (list<Enemy*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); it++)
		{
			travelDirection = Vector3((rand() % -50), 0.0f, (rand() % -50));

			if (!(*it)->isAlive())
			{
				(*it)->Spawn(initialLocation, 5*Vector3::One, travelDirection, Vector3::One);
				break;
			}
		}
	}
	checkForCollisions(_GD);
}


void EnemyManager::checkForCollisions(GameData* _GD)
{
	for (list<Enemy*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); it++)
	{
		for (list<Bullet*>::iterator it2 = player_Bullets.begin(); it2 != player_Bullets.end(); it2++)
		{
			if ((*it2)->isAlive() && (*it)->isAlive())
			{
				if (_GD->m_CM.CheckForCollision((*it)->GetPos(), (*it2)->GetPos()))
				{
					increaseEnemyScore();
					(*it)->SetAlive(false);
					(*it2)->SetAlive(false);
				}
			}
		}
		(*it)->Tick(_GD);
	}

}

void EnemyManager::increaseEnemyScore()
{
	enemyScore += 10;
}

list<Enemy*> EnemyManager::GetEnemy()
{
	return m_Enemies;
}


void EnemyManager::Draw(ID3D11DeviceContext * _pd3dImmediateContext, CommonStates * _states, Camera * _cam)
{
	for (list<Enemy*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); it++)
	{
		(*it)->Draw(_pd3dImmediateContext, _states, _cam);
	}	
}

int EnemyManager::getEnemyScore()
{
	return enemyScore;
}


