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
	Bullet *bullet;
public:
	Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~Metroid();

	LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath);
	bool CheckCollision(Samus* a, SpiderBug* b);
	float SweptAABB(GameObject *a, GameObject *b, float &normalX, float &normalY);

	virtual void ObjectCollision(int Delta);
	virtual void UpdateWorld(int Delta);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
};
