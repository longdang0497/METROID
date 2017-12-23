#pragma once
#include "Enemy.h"
#include "Define.h"

class FlyingBat : public Enemy
{
private:
	Sprite *Bat;
	World * world;
public:
	FlyingBat();
	FlyingBat(LPD3DXSPRITE spriteHandler, World * manager);
	~FlyingBat();

	void CreateBat(LPDIRECT3DDEVICE9 d3ddv);
	virtual void Render();
	virtual void UpdateObject(int Delta);
	//void UpdateCollison(GameObject* _simon, vector<GameObject*>, Game*, float);
	ObjectType GetType() { return typeBAT; }
};
