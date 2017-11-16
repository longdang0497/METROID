#pragma once
#include "Game.h"
#include "Define.h"
#include "Samus.h"
#include "FlyingBat.h"
#include "SpiderBug.h"

class Metroid : public Game
{
private:
	LPDIRECT3DSURFACE9 _Background;
	Samus *samus;
	FlyingBat *bat;
	SpiderBug *spider;
public:
	Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~Metroid();

	LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath);

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
};
