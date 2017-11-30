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
	void _CreateBullets(int X = 0, int Y = 0, int VX = 0, int VY = 0);
	virtual void UpdateObject(int delta);
	virtual void Render();
};
