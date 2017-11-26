#pragma once
#include <d3d9.h>
#include <d3dx9.h>

using namespace std;

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _Image;				// The "container"
	LPD3DXSPRITE _SpriteHandler;
	LPWSTR _Coord;	

	RECT srect;
	int _Index;								// Current sprite index
	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
public:
	D3DXVECTOR3 position;
	Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, LPWSTR Coord, int Width, int Height, int Count, int SpritePerRow);
	float getpos_x();
	void setpos_x(float x);
	float getpos_y();
	void setpos_y(float y);

	int getwidth();
	int getheight();

	RECT getrec();
	void setrec(RECT value);

	RECT ReadCoord();

	void Next();
	void Reset();

	// Render current sprite at location (X,Y)
	void Render(int pos_x, int pos_y, int vpx, int vpy);
	~Sprite();
};

