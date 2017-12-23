#include "SpiderBug.h"

SpiderBug::SpiderBug()
{
	spiderbug = NULL;
}

SpiderBug::SpiderBug(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	//Collider
	collider = new Collider();
}

SpiderBug::~SpiderBug()
{
	delete spiderbug;
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
	if (d3ddv == NULL) return;
	
	//Create instance of sprites
	spiderbug = new Sprite(spriteHandler, ENEMIES_SPRITES_PATH, SPIDER_MOVEMENT, SPIDER_WIDTH, SPIDER_HEIGHT, SPIDER_COUNT, SPRITE_PER_ROW);
	spiderbug_wall_left = new Sprite(spriteHandler, ENEMIES_SPRITES_PATH, SPIDER_WALL_LEFT_MOVEMENT, SPIDER_WALL_WIDTH, SPIDER_WALL_HEIGHT, SPIDER_COUNT, SPRITE_PER_ROW);
	spiderbug_wall_right = new Sprite(spriteHandler, ENEMIES_SPRITES_PATH, SPIDER_WALL_RIGHT_MOVEMENT, SPIDER_WALL_WIDTH, SPIDER_WALL_HEIGHT, SPIDER_COUNT, SPRITE_PER_ROW);

	_x = 450;
	_y = GROUND_Y;

	_vx = 0;
	_vx_last = 1.0f;
	_vy = 0;
	rigidBody = D3DXVECTOR2(16,16);
}

void SpiderBug::Render()
{
	float vpx = 0;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	spiderbug->Render(_x, _y);
	//spiderbug_wall_left->Render(_x, _y, vpx, VIEW_PORT_Y);
	//spiderbug_wall_right->Render(_x, _y, vpx, VIEW_PORT_Y);
	spriteHandler->End();
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
	Render();
}