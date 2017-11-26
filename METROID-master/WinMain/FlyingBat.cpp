#include "FlyingBat.h"

FlyingBat::FlyingBat()
{
	Bat = NULL;
}

FlyingBat::~FlyingBat()
{
	delete(Bat);
}

void FlyingBat::CreateBat(LPDIRECT3DDEVICE9 d3ddv)
{
	HRESULT res = D3DXCreateSprite(d3ddv, &_SpriteHandler);

	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create instance of sprites
	Bat = new Sprite(_SpriteHandler, ENEMIES_SPRITES_PATH, BAT_MOVEMENT, BAT_WIDTH, BAT_HEIGHT, BAT_COUNT, SPRITE_PER_ROW);

	_x = 350;
	_y = 450;

	_vx = 0;
	_vx_last = 1.0f;
	_vy = 0;
}

void FlyingBat::RenderBat()
{
	int vpx = 0;
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	Bat->Render(_x, _y, vpx, VIEW_PORT_Y);
	_SpriteHandler->End();
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
		/*if (_vx > 0) samus_right->Next();
		if (_vx < 0) samus_left->Next();*/
		Bat->Next();
		last_time = now;
	}
	RenderBat();
}

void FlyingBat::UpdateCollison(GameObject * _simon, vector<GameObject*>, Game *, float)
{
}
