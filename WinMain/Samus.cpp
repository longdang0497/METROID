#include "Samus.h"
#include <d3dx9.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

#define SAMUS_SPEED 0.2f

#define BACKGROUND_FILE L"map_demo.png"
#define SAMUS_SPRITES_PATH L"samus_sprites.png"

#define APPEARING L"sprites\\appearing.txt"

#define JUMP_LEFT L"sprites\\jump_left.txt"
#define JUMP_RIGHT L"sprites\\jump_right.txt"

#define RUN_SHOOTING_LEFT L"sprites\\RUN_SHOOTING_LEFT.txt"
#define RUN_SHOOTING_RIGHT L"sprites\\RUN_SHOOTING_RIGHT.txt"
#define RUN_AIM_UP_LEFT L"sprites\\RUN_AIM_UP_LEFT.txt"
#define RUN_AIM_UP_RIGHT L"sprites\\RUN_AIM_UP_RIGHT.txt"

#define IDLE_AIM_UP_LEFT L"sprites\\IDLE_AIM_UP_LEFT.txt"
#define IDLE_AIM_UP_RIGHT L"sprites\\IDLE_AIM_UP_RIGHT.txt"

#define RUNNING_LEFT L"running_left.txt"
#define RUNNING_RIGHT L"running_right.txt"

#define STANDING_LEFT L"sprites\\standing_left.txt"
#define STANDING_RIGHT L"sprites\\standing_right.txt"

#define APPEARING_WIDTH 16
#define APPEARING_HEIGHT 32
#define RUNNING_WIDTH 23
#define RUNNING_HEIGHT 38
#define STANDING_WIDTH 21
#define STANDING_HEIGHT 32
#define RUN_SHOOTING_WIDTH 25
#define RUN_SHOOTING_HEIGHT 31
#define RUN_AIM_UP_WIDTH 19
#define RUN_AIM_UP_HEIGHT 38
#define JUMP_WIDTH 18
#define JUMP_HEIGHT 25
#define IDLE_AIM_UP_WIDTH 14
#define IDLE_AIM_UP_HEIGHT 38

#define APPEARING_COUNT 5
#define RUNNING_COUNT 3
#define JUMP_COUNT 1
#define RUN_SHOOTING_COUNT 3
#define RUN_AIM_UP_COUNT 3
#define IDLE_AIM_UP_COUNT 1
#define STANDING_COUNT 1

#define GROUND_Y 95
#define ANIMATE_RATE 30
#define JUMP_VELOCITY_BOOST 3.0f
#define FALLDOWN_VELOCITY_DECREASE 0.5f

#define VIEW_PORT_Y  600

Samus::Samus(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) : Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	//samus_appearing = NULL;
	samus_right = NULL;
	samus_left = NULL;
}

Samus::~Samus()
{
	delete(samus_appearing);
	delete(samus_right);
	delete(samus_left);
}

LPDIRECT3DSURFACE9 Samus::CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath)
{
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(NULL, L"[ERROR] Failed to get image info.", NULL, NULL);
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;

	d3ddv->CreateOffscreenPlainSurface(
		info.Width,				// width
		info.Height,			// height
		D3DFMT_X8R8G8B8,		// format
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	result = D3DXLoadSurfaceFromFile(
		surface, 		// surface
		NULL,			// destination palette	
		NULL,			// destination rectangle 
		FilePath,
		NULL,			// source rectangle
		D3DX_DEFAULT, 	// filter image
		D3DCOLOR_XRGB(0, 0, 0),				// transparency (0 = none)
		NULL);			// reserved

	if (result != D3D_OK)
	{
		MessageBox(NULL, L"[ERROR] D3DXLoadSurfaceFromFile() failed", NULL, NULL);
		return NULL;
	}

	return surface;
}

void Samus::SetVelocityX(float value)
{
	samus_vx = value;
}

float Samus::GetVelocityX()
{
	return samus_vx;
}

void Samus::SetVelocityXLast(float value)
{
	samus_vx_last = value;
}

float Samus::GetVelocityXLast()
{
	return samus_vx_last;
}

SamusStates Samus::GetState()
{
	return state;
}

void Samus::SetState(SamusStates value)
{
	state = value;
}

void Samus::RenderSpriteSamus(int _count)
{
	
}

void Samus::SpriteReset()
{
	//samus_appearing->Reset();
	samus_left->Reset();
	samus_right->Reset();
}

void Samus::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	samus_x += samus_vx * Delta;
	samus_y += samus_vy * Delta;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (samus_vx > 0) samus_right->Next();	
		if (samus_vx < 0) samus_left->Next();
		last_time = now;
	}
	

	if (samus_y > GROUND_Y) samus_vy -= FALLDOWN_VELOCITY_DECREASE;
	else
	{
		samus_y = GROUND_Y;
		samus_vy = 0;
	}
	
	// Background
	d3ddv->StretchRect(
	_Background,			// from
	NULL,				// which portion?
	_BackBuffer,		// to
	NULL,				// which portion?
	D3DTEXF_NONE);

	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	int vpx = 0;
	/*switch (state)
	{
	case RIGHTING:
		samus_right->Render(samus_x, samus_y, vpx, VIEW_PORT_Y);
		break;
	case LEFTING:
		samus_left->Render(samus_x, samus_y, vpx, VIEW_PORT_Y);
		break;
	}*/

	//
	//  Select correct sprite to render depends on which direction mario is facing
	//

	//samus_appearing->Render(samus_x, samus_y, vpx, VIEW_PORT_Y);
	if (samus_vx > 0)			samus_right->Render(samus_x, samus_y, vpx, VIEW_PORT_Y);
	else if (samus_vx < 0)		samus_left->Render(samus_x, samus_y, vpx, VIEW_PORT_Y);
	else if (samus_vx_last < 0) samus_left->Render(samus_x, samus_y, vpx, VIEW_PORT_Y);
	else						samus_right->Render(samus_x, samus_y, vpx, VIEW_PORT_Y);

	_SpriteHandler->End();
}

void Samus::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	if (IsKeyDown(DIK_RIGHT))
	{
		samus_vx = SAMUS_SPEED;
		samus_vx_last = samus_vx;
	}
	else
		if (IsKeyDown(DIK_LEFT))
		{
			samus_vx = -SAMUS_SPEED;
			samus_vx_last = samus_vx;
		}
		else
		{
			samus_vx = 0;
			samus_left->Reset();
			samus_right->Reset();
		}
}

void Samus::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	// TO-DO: not a very good place to initial sprite handler
	_Background = CreateSurfaceFromFile(_d3ddv, BACKGROUND_FILE);

	HRESULT res = D3DXCreateSprite(_d3ddv, &_SpriteHandler);

	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return; 

	//Create instance of sprites
	samus_appearing = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, APPEARING, APPEARING_WIDTH, APPEARING_HEIGHT, APPEARING_COUNT, SPRITE_PER_ROW);
	samus_right = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUNNING_RIGHT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	samus_left = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUNNING_LEFT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);

	samus_x = 50;
	samus_y = GROUND_Y;

	samus_vx = 0;
	samus_vx_last = 1.0f;
	samus_vy = 0;

	//Init state of samus
	state = IDLE_RIGHT;
}

void Samus::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (samus_y <= GROUND_Y) samus_vy += JUMP_VELOCITY_BOOST;			// start jump if is not "on-air"
		break;
	}
}
