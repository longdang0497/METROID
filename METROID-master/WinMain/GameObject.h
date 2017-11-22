#pragma once
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"

class GameObject
{
protected:
	//RECT rectObject;

	int _width;
	int _height;

	int _x;
	int _y;

	float _vx;
	float _vy;

	float _vx_last;

	DWORD last_time;
public:
	GameObject();
	GameObject(int X, int Y, float Vx, float Vy);
	~GameObject();

	virtual void SetRECT(RECT value);
	virtual	RECT GetRECT();

	void SetX(float value);
	float GetX();
	void SetY(float value);
	float GetY();

	void SetVx(float value);
	float GetVx();
	void SetVy(float value);
	float GetVy();

	void SetVelocityXLast(float value);
	float GetVelocityXLast();

	void SetWidth(int value);
	int GetWidth();
	void SetHeight(int value);
	int GetHeight();

	virtual void UpdateObject(int delta);
	virtual void Render();
};
