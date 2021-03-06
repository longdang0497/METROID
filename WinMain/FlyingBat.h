#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "Define.h"

class FlyingBat : public GameObject
{
private:
	LPD3DXSPRITE _SpriteHandler;
	Sprite *Bat;
public:
	FlyingBat();
	~FlyingBat();

	void CreateBat(LPDIRECT3DDEVICE9 d3ddv);
	void RenderBat();
	void UpdateObject(int Delta);
};
