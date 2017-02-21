#ifndef _VEHICLE_H_
#define _VEHICLE_H_
#include "CMOGO.h"
#include "gameobject.h"
#include "CollisionManager.h"

class Vehicle : public CMOGO
{

public:

	Vehicle(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll, Vector3 _scale, float _radius);

	~Vehicle();
	int getPlayerScore();
	void increaseScore();

	//void checkForCollisions(GameData* _GD);
	Vector3 GetPos();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(ID3D11DeviceContext* _pd3dImmediateContext, CommonStates* _states, Camera* _cam) override;

protected:
	Vector3 forwards;
	int playerScore = 0;
};

#endif