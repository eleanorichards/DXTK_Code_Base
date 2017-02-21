#include "CollisionManager.h"

bool CollisionManager::CheckForCollision(Vector3 _aPos, Vector3 _bPos)
{
	if (Vector3::Distance(_aPos, _bPos) <= 30)
	{
		return true;
	}
	return false;
}
