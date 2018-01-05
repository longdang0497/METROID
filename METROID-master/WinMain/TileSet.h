#pragma once
#include "Tile.h"
#include <vector>

class TileSet
{
private:
	Sprite * _tileImage; // reference tới TileSet Image
	vector<Tile*> _listTiles; // list chứa các Tile
public:
	TileSet(ObjectType _type);
	~TileSet();

	// Đọc TileSet từ file text
	//void loadListTiles(LPWSTR tileSet);

	// Vẽ 1 ô Tile với id tương ứng. Gọi hàm này trong TileMap
	//void draw(LPD3DXSPRITE spriteHandle, int id, D3DXVECTOR2 position, Camera *viewport);

	//Sprite* getSprite();
};
