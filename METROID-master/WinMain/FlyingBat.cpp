#include "FlyingBat.h"

FlyingBat::FlyingBat()
{
	Bat = NULL;
}

FlyingBat::FlyingBat(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	//Collider
	collider = new Collider();
}

FlyingBat::~FlyingBat()
{
	delete(Bat);
}

void FlyingBat::CreateBat(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;

	//Create instance of sprites
	Bat = new Sprite(spriteHandler, ENEMIES_SPRITES_PATH, BAT_MOVEMENT, BAT_WIDTH, BAT_HEIGHT, BAT_COUNT, SPRITE_PER_ROW);

	_x = 350;
	_y = 450;

	_vx = 0;
	_vx_last = 1.0f;
	_vy = 0;
}

void FlyingBat::Render()
{
	float vpx = 0;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	Bat->Render(_x, _y);
	spriteHandler->End();
}

void FlyingBat::UpdateObject(int Delta)
{
	//
	// Update position
	//
	_x += _vx * Delta;
	_y += _vy * Delta;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		Bat->Next();
		last_time = now;
	}
	Render();
}
