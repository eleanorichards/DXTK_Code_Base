#pragma once
#ifndef _TERRAIN_H_
#define _TERRAIN_H_
#include "CMOGO.h"

class Terrain : public CMOGO
{
public:
	Terrain(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll, Vector3 _scale);
	~Terrain();

protected:

	virtual void Tick(GameData* _GD) override
	{};
};

#endif