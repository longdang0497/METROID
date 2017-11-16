#include "SpiderBug.h"

#include "FlyingBat.h"

SpiderBug::SpiderBug()
{
	spiderbug = NULL;
}

SpiderBug::~SpiderBug()
{
	delete(spiderbug);
}

void SpiderBug::CreateSpiderBug(LPDIRECT3DDEVICE9 d3ddv)
{
	HRESULT res = D3DXCreateSprite(d3ddv, &_SpriteHandler);

	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create instance of sprites
	spiderbug = new Sprite(_SpriteHandler, ENEMIES_SPRITES_PATH, SPIDER_MOVEMENT, SPIDER_WIDTH, SPIDER_HEIGHT, SPIDER_COUNT, SPRITE_PER_ROW);

	_x = 40;
	_y = GROUND_Y;

	_vx = 0;
	_vx_last = 1.0f;
	_vy = 0;
}

void SpiderBug::RenderSpiderBug()
{
	int vpx = 0;
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	spiderbug->Render(_x, _y, vpx, VIEW_PORT_Y);
	_SpriteHandler->End();
}

void SpiderBug::UpdateObject(int Delta)
{
	//
	// Update position
	//
	_x += (_vx + 0.2) * Delta;
	_y += _vy * Delta;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		/*if (_vx > 0) samus_right->Next();
		if (_vx < 0) samus_left->Next();*/
		spiderbug->Next();
		last_time = now;
	}
	RenderSpiderBug();
}
