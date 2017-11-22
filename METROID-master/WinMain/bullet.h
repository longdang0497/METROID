#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Timer.h"

class Bullet : public GameObject
{
private:
	LPD3DXSPRITE _SpriteHandler;
	Sprite *bullet;
	Timer *timer;
public:
	Bullet();
	~Bullet();

	void SetX(float value);
	float GetX();
	void SetY(float value);
	float GetY();

	void SetVx(float value);
	float GetVx();

	void CreateBullet(LPDIRECT3DDEVICE9 d3ddv);
	void RenderBullet();
	void MoveRight(int Delta);
	void MoveLeft(int Delta);
};