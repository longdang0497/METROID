#include "Sprite.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Camera.h"

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, LPWSTR Coord, int Width, int Height, int Count, int SpritePerRow)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	//Default the sprite to position (0, 0, 0)
	position.x = 0;
	position.y = 0;
	position.z = 0;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;
	_Coord = Coord;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(NULL, L"[ERROR] Failed to get information from image file.", FilePath, NULL);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		MessageBox(NULL, L"[ERROR] Failed to create texture from file.", NULL, NULL);
		return;
	}
}

float Sprite::getpos_x()
{
	return (float)position.x;
}

void Sprite::setpos_x(float x)
{
	(float)position.x = x;
}

float Sprite::getpos_y()
{
	return (float)position.y;
}

void Sprite::setpos_y(float y)
{
	(float)position.y = y;
}

int Sprite::getwidth()
{
	return _Width;
}

int Sprite::getheight()
{
	return _Height;
}

RECT Sprite::getrec()
{
	RECT _srect = ReadCoord();
	return _srect;
}

void Sprite::setrec(RECT value)
{
	srect = value;
}

RECT Sprite::ReadCoord()
{
	int ** coord = new int*[2];
	ifstream f;
	try {
		f.open(_Coord);
		for (int i = 0; i < _Count; i++)
		{
			if (!f.eof())
			{
				coord[i] = new int[_Count];
				f >> coord[i][0];
				if (coord[i][0] != '\t' && coord[i][0] != '\n') srect.left = coord[i][0];
				f >> coord[i][1];
				if (coord[i][1] != '\t' && coord[i][1] != '\n') srect.top = coord[i][1];
				srect.right = srect.left + _Width;
				srect.bottom = srect.top + _Height + 1;
			}

			if (i == _Index)
			{
				break;
			}
		}
		f.close();
	}
	catch (exception e) {}
	return srect;
}

void Sprite::Next()
{
	_Index = (_Index + 1) % _Count;
}

void Sprite::Reset()
{
	_Index = 0;
}

void Sprite::Render(int X, int Y, int vpx, int vpy)
{
	RECT rec_sprite = ReadCoord();
	//D3DXVECTOR3 position((float)X, (float)Y, 0);
	position.x = X;
	position.y = Y;

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = (float)-vpx;
	mt._42 = (float)vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	/*D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, 1.5, 1.5, 1);
	_SpriteHandler->SetTransform(&mt1);*/
	//Camera *cam = new Camera(800, 600,);

	_SpriteHandler->Draw(
		_Image,
		&rec_sprite,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255));
}

Sprite::~Sprite()
{
	_Image->Release();
}
