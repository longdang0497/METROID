#pragma once
#include "Game.h"
#include "Sprite.h"
#include <dinput.h>

#define SPRITE_PER_ROW 1

enum SamusStates {
	IDLE_LEFT,
	IDLE_RIGHT,
	LEFTING,
	RIGHTING,
	IDLING_AIM_UP_LEFT,
	IDLING_AIM_UP_RIGHT,
	AIMING_UP_LEFT,
	AIMING_UP_RIGHT,
	TRANSFORM_LEFT,
	TRANSFORM_RIGHT,
};

class Samus : public Game
{
protected:
	LPD3DXSPRITE _SpriteHandler;
	LPDIRECT3DSURFACE9 _Background;

	int samus_x;			// position of kitty
	int samus_y;

	float samus_vx;			// velocity of kitty
	float samus_vy;

	float samus_vx_last;	// last vx of mario before stop ( to determine the direction of mario )

	DWORD last_time;		// this is to control the animate rate of kitty

							//LPDIRECT3DSURFACE9 Background;
	SamusStates state;
	Sprite *samus_appearing;
	Sprite *samus_right;
	Sprite *samus_left;
public:
	Samus(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~Samus();

	LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath);

	void SetVelocityX(float value);
	float GetVelocityX();

	void SetVelocityXLast(float value);
	float GetVelocityXLast();

	SamusStates GetState();
	void SetState(SamusStates value);

	void RenderSpriteSamus(int _count);
	void SpriteReset();

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
};
