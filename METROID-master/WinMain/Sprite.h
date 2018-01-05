#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Camera.h"

using namespace std;

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _Image;	// The "container"
	LPD3DXSPRITE _SpriteHandler;
	LPWSTR _Coord;	

	D3DXVECTOR3 position;
	RECT srect;
	int _Index;								// Current sprite index
	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
public:
	Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, LPWSTR Coord, int Width, int Height, int Count, int SpritePerRow);
	~Sprite();

	RECT ReadCoord();

	int GetIndex();
	void SetIndex(int value);

	void Next();
	void Reset();

	// Render current sprite at location (X,Y)
	void Render(float pos_x, float pos_y);
};

