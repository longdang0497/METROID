#include "Ground_Rock.h"

GroundRock::GroundRock()
{
	rock = NULL;
}

GroundRock::~GroundRock()
{
	delete rock;
}

void GroundRock::CreateSpiderBug(LPDIRECT3DDEVICE9 d3ddv)
{
	HRESULT res = D3DXCreateSprite(d3ddv, &_SpriteHandler);

	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;
	
	//rock = new Sprite();

	_x = 450;
	_y = 800;
}

void GroundRock::Render()
{
	int vpx = 0;
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	rock->Render(_x, _y, vpx, VIEW_PORT_Y);
	_SpriteHandler->End();
}
