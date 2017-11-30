#pragma once
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
	virtual void Render();
	virtual void UpdateObject(int Delta);
	void UpdateCollison(GameObject* _simon, vector<GameObject*>, Game*, float);
	ObjectType GetType() { return typeBAT; }
};
