#pragma once
#include "d3dx9.h"
#include "GameObject.h"

class TextSprite : public GameObject
{
private:
	LPWSTR _text;
	D3DXVECTOR2 _position; // tọa độ top-left
public:
	TextSprite(LPWSTR text, D3DXVECTOR2 position, LPD3DXSPRITE spriteHandle);
	~TextSprite();

	D3DXVECTOR2 getPosition();
	void setPosition(D3DXVECTOR2 position);

	void setText(LPWSTR text);
	void _DrawText(LPD3DXSPRITE spriteHandle);
};
