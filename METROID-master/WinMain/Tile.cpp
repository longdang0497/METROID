#include "Tile.h"

Tile::Tile(int tID, Sprite * tile, RECT recTile)
{
	tileID = tID;
	_tile = tile;
	_tileRECT = recTile;
}

Tile::~Tile()
{
}

int Tile::getID()
{
	return tileID;
}

void Tile::draw(LPD3DXSPRITE spriteHandle, float _x, float _y)
{
	if (_tile == nullptr) return;
	_tile->Render(_x, _y);
}
