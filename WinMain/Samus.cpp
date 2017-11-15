#include "Samus.h"
#include <d3dx9.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Define.h"

Samus::Samus()
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

void Samus::CreateSamus(LPDIRECT3DDEVICE9 d3ddv)
{
	HRESULT res = D3DXCreateSprite(d3ddv, &_SpriteHandler);

	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create instance of sprites
	samus_appearing = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, APPEARING, APPEARING_WIDTH, APPEARING_HEIGHT, APPEARING_COUNT, SPRITE_PER_ROW);
	samus_right = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUNNING_RIGHT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	samus_left = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUNNING_LEFT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);

	_x = 50;
	_y = GROUND_Y;

	_vx = 0;
	_vx_last = 1.0f;
	_vy = 0;

	//Init state of samus
	state = IDLE_RIGHT;
}

void Samus::SetX(float value)
{
	_x = value;
}

float Samus::GetX()
{
	return _x;
}

void Samus::SetY(float value)
{
	_y = value;
}

float Samus::GetY()
{
	return _y;
}

void Samus::SetVelocityX(float value)
{
	_vx = value;
}

float Samus::GetVelocityX()
{
	return _vx;
}

void Samus::SetVelocityY(float value)
{
	_vy = value;
}

float Samus::GetVelocityY()
{
	return _vy;
}

void Samus::SetVelocityXLast(float value)
{
	_vx_last = value;
}

float Samus::GetVelocityXLast()
{
	return _vx_last;
}

SamusStates Samus::GetState()
{
	return state;
}

void Samus::SetState(SamusStates value)
{
	state = value;
}

void Samus::UpdateObject(int delta)
{
	srand((unsigned)time(NULL));
	_x += _vx * delta;
	_y += _vy * delta;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (_vx > 0) samus_right->Next();
		if (_vx < 0) samus_left->Next();
		last_time = now;
	}
	RenderSpriteSamus();

	if (_y > GROUND_Y) _vy -= FALLDOWN_VELOCITY_DECREASE;
	else
	{
		_y = GROUND_Y;
		_vy = 0;
	}
}

void Samus::RenderSpriteSamus()
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	int vpx = 0;
	if (_vx > 0)			samus_right->Render(_x, _y, vpx, VIEW_PORT_Y);
	else if (_vx < 0)		samus_left->Render(_x, _y, vpx, VIEW_PORT_Y);
	else if (_vx_last < 0) samus_left->Render(_x, _y, vpx, VIEW_PORT_Y);
	else						samus_right->Render(_x, _y, vpx, VIEW_PORT_Y);

	_SpriteHandler->End();
}

void Samus::SpriteReset()
{
	//samus_appearing->Reset();
	samus_left->Reset();
	samus_right->Reset();
}







