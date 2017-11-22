#pragma once
#include "GameObject.h"
#include "Define.h"

class GroundRock : public GameObject
{
private:
	LPD3DXSPRITE _SpriteHandler;
	Sprite *rock;
public:
	GroundRock();
	~GroundRock();

	void CreateSpiderBug(LPDIRECT3DDEVICE9 d3ddv);
	void RenderSpiderBug();
};