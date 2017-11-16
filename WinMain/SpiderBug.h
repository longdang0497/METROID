#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "Define.h"

class SpiderBug : public GameObject
{
private:
	LPD3DXSPRITE _SpriteHandler;
	Sprite *spiderbug;
public:
	SpiderBug();
	~SpiderBug();

	void CreateSpiderBug(LPDIRECT3DDEVICE9 d3ddv);
	void RenderSpiderBug();
	void UpdateObject(int Delta);
};
