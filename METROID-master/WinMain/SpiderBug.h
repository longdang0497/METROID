#pragma once
#include "Sprite.h"
#include "Enemy.h"
#include "Define.h"

enum SpiderStates
{
	WALL_LEFT,
	WALL_RIGHT,
	STRAIGHT,
	WAS_SHOT,
	DIE
};

class SpiderBug : public Enemy
{
private:
	Sprite *spiderbug;
	Sprite *spiderbug_wall_left;
	Sprite *spiderbug_wall_right;
	//Sprite *spiderbug_was_shot;
	SpiderStates _state;
public:
	SpiderBug();
	SpiderBug(LPD3DXSPRITE spriteHandler, World * manager);
	~SpiderBug();

	void SetSpiderState(SpiderStates value);
	SpiderStates GetSpiderState();

	void CreateSpiderBug(LPDIRECT3DDEVICE9 d3ddv);
	void Render();
	virtual void UpdateObject(int Delta);
	//void UpdateCollison(GameObject* _simon, vector<GameObject*>, Game*, float);
	ObjectType GetType() { return typeSpiderBug; }
};
