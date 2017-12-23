#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Timer.h"

enum BulletDirection
{
	SHOOT_UP,
	SHOOT_LEFT, 
	SHOOT_RIGHT
};

class Bullet : public GameObject
{
private:
	LPD3DXSPRITE _SpriteHandler;
	LPDIRECT3DDEVICE9* m_d3ddv;
	Sprite *bullet;
	Timer *timer;
	BulletDirection bulletdir;
	bool isRender;
public:
	Bullet(LPDIRECT3DDEVICE9* d3ddv, float X = 0, float Y = 0, float VX = 0, float VY = 0);
	~Bullet();

	void SetState(BulletDirection value);
	BulletDirection GetState();

	//virtual void UpdateObject(float delta);
	virtual void Render();
	void CreateBullet();
	void UpdateObject(float Delta);
	bool isRendering();
	//void UpdateCollison(GameObject* _simon, vector<GameObject*>, Game*, float);
};