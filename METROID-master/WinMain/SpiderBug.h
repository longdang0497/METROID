#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "Define.h"

enum SpiderStates
{
	WALL_LEFT,
	WALL_RIGHT,
	STRAIGHT
};

class SpiderBug : public GameObject
{
private:
	LPD3DXSPRITE _SpriteHandler;
	Sprite *spiderbug;
	Sprite *spiderbug_wall_left;
	Sprite *spiderbug_wall_right;
	SpiderStates _state;
public:
	SpiderBug();
	~SpiderBug();

	virtual void setRECT(RECT value);
	RECT getRECTSpider();

	void SetX(float value);
	float GetX();
	void SetY(float value);
	float GetY();

	void SetVx(float value);
	float GetVx();

	void SetSpiderState(SpiderStates value);
	SpiderStates GetSpiderState();

	void CreateSpiderBug(LPDIRECT3DDEVICE9 d3ddv);
	void RenderSpiderBug();
	void UpdateObject(int Delta);
};
