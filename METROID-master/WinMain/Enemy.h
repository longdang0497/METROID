#pragma once
#include "Define.h"
#include "GameObject.h"

class Enemy : public GameObject
{
public :
	int width;
	int height;
public :
	Enemy();
	Enemy(LPD3DXSPRITE spriteHandler, World * manager);
	~Enemy();
};