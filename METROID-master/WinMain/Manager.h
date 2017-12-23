#pragma once
#include "bullet.h"

class Manager
{
private:
	LPD3DXSPRITE _SpriteHandler;
	LPDIRECT3DDEVICE9 m_d3ddv;
	vector<Bullet*> weapon = vector<Bullet*>(0);
public:
	Manager(LPDIRECT3DDEVICE9 d3ddv);
	~Manager();

	void CheckDistance();
	void _CreateBullets(float X = 0, float Y = 0, float VX = 0, float VY = 0);
	virtual void UpdateObject(float delta);
	virtual void Render();
};
