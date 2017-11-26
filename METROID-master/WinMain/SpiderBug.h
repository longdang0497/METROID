#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "Define.h"

enum SpiderStates
{
	WALL_LEFT,
	WALL_RIGHT,
	STRAIGHT,
	WAS_SHOT,
	DIE
};

class SpiderBug : public GameObject
{
private:
	LPD3DXSPRITE _SpriteHandler;
	Sprite *spiderbug;
	Sprite *spiderbug_wall_left;
	Sprite *spiderbug_wall_right;
	//Sprite *spiderbug_was_shot;
	SpiderStates _state;
public:
	SpiderBug();
	~SpiderBug();

	void SetSpiderState(SpiderStates value);
	SpiderStates GetSpiderState();

	void CreateSpiderBug(LPDIRECT3DDEVICE9 d3ddv);
	void RenderSpiderBug();
	void UpdateObject(int Delta);
	void UpdateCollison(GameObject* _simon, vector<GameObject*>, Game*, float);
	ObjectType GetType() { return typeSpiderBug; }
};
