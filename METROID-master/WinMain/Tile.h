#pragma once
#include "Sprite.h"

// Dùng để lưu thông tin của 1 ô Tile (id và srcRect)
class Tile
{
private:
	int tileID;
	Sprite * _tile;
	RECT _tileRECT;
public:
	Tile(int tID, Sprite * tile, RECT recTile);
	~Tile();

	int getID();
	void draw(LPD3DXSPRITE spriteHandle, float _x, float _y);
};