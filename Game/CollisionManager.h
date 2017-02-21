#pragma once
#include <d3d11.h>
#include "SimpleMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


class CollisionManager
{
public:

	bool CheckForCollision(Vector3 _aPos, Vector3 _bPos);

private:
	/*Vector3 _aPos;
	Vector3 _bPos;*/

};

