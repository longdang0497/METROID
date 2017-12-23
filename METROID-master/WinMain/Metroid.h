#pragma once
#include "Game.h"
#include "bullet.h"
#include "Timer.h"
#include <time.h>
#include "Manager.h"
#include "World.h"
class Metroid : public Game
{
private:
	Manager* manager;
	Timer *timer;
	World * world;
	GameObject *obj;
	CSound *audio;
	GameSound *sound;

	DWORD start_jump;
	DWORD now_jump;
	DWORD tick_per_frame;

	DWORD start_shoot;
	DWORD now_shoot;
	vector<GameObject*> Player = vector<GameObject*>(0);
public:
	Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, float FrameRate);
	~Metroid();

	LPD3DXSPRITE _spriteHandler;
	LPDIRECT3DSURFACE9 _Background;
	LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath);

	void ShootBullet(BulletDirection bullDir);

	bool CheckCollision(RECT a, RECT b);

	virtual void UpdateWorld(float Delta);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
};
