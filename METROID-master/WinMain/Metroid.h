#pragma once
#include "Game.h"
#include "FlyingBat.h"
#include "SpiderBug.h"
#include "bullet.h"
#include "Timer.h"

class Metroid : public Game
{
private:
	Timer *timer;
	LPDIRECT3DSURFACE9 _Background;
	Samus *samus;
	FlyingBat *bat;
	SpiderBug *spider;
	Bullet *bullets[MAX_BULLETS] = { NULL };
	GameObject *obj;
public:
	Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~Metroid();

	LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath);
	bool CheckCollision(RECT a, RECT b);
	float SweptAABB(GameObject *a, GameObject *b, float &normalX, float &normalY);

	void AddBullet(int x, int y, int vx);
	void RemoveBullet(int id);
	void CheckShot();
	virtual void ObjectCollision(int Delta);
	virtual void UpdateWorld(int Delta);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
};
