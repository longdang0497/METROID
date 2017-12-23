#include "Ground_Rock.h"

GroundRock::GroundRock()
{
	rock = NULL;
}

GroundRock::~GroundRock()
{
	delete rock;
}

void GroundRock::CreateRock(LPDIRECT3DDEVICE9 d3ddv)
{
	HRESULT res = D3DXCreateSprite(d3ddv, &_SpriteHandler);

	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;
	
	rock = new Sprite(_SpriteHandler, MAP_ROCK, BRICK, MAP_ROCK_WIDTH, MAP_ROCK_HEIGHT, 1,SPRITE_PER_ROW);

	_x = 320;
	_y = GROUND_Y;

	_vx = 0;
	_vy = 0;
	_vx_last = 0;
}

void GroundRock::Render()
{
	float vpx = 0;
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	rock->Render(_x, _y);
	_SpriteHandler->End();
}
