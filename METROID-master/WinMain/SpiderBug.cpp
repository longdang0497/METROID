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

void SpiderBug::setRECT(RECT value)
{
	spiderbug->getrec() = value;
}

RECT SpiderBug::getRECTSpider()
{
	return spiderbug->getrec();
}

void SpiderBug::SetX(float value)
{
	_x = value;
}

float SpiderBug::GetX()
{
	return _x;
}

void SpiderBug::SetY(float value)
{
	_y = value;
}

float SpiderBug::GetY()
{
	return _y;
}

void SpiderBug::SetVx(float value)
{
	_vx = value;
}

float SpiderBug::GetVx()
{
	return _vx;
}

void SpiderBug::SetSpiderState(SpiderStates value)
{
	_state = value;
}

SpiderStates SpiderBug::GetSpiderState()
{
	return _state;
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
	spiderbug_wall_left = new Sprite(_SpriteHandler, ENEMIES_SPRITES_PATH, SPIDER_WALL_LEFT_MOVEMENT, SPIDER_WALL_WIDTH, SPIDER_WALL_HEIGHT, SPIDER_COUNT, SPRITE_PER_ROW);
	spiderbug_wall_right = new Sprite(_SpriteHandler, ENEMIES_SPRITES_PATH, SPIDER_WALL_RIGHT_MOVEMENT, SPIDER_WALL_WIDTH, SPIDER_WALL_HEIGHT, SPIDER_COUNT, SPRITE_PER_ROW);

	_x = 450;
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
	//spiderbug_wall_left->Render(_x, _y, vpx, VIEW_PORT_Y);
	//spiderbug_wall_right->Render(_x, _y, vpx, VIEW_PORT_Y);
	_SpriteHandler->End();
}

void SpiderBug::UpdateObject(int Delta)
{
	//
	// Update position
	//
	//float rd = rand();
	_x += (_vx - SPIDER_SPEED) * Delta;
	_y += _vy * Delta;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		/*if (_vx > 0) samus_right->Next();
		if (_vx < 0) samus_left->Next();*/
		spiderbug->Next();
		//spiderbug_wall_left->Next();
		//spiderbug_wall_right->Next();
		last_time = now;
	}
	RenderSpiderBug();
}
