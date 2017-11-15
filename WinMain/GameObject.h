#pragma once
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>


class GameObject
{
protected:
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

	virtual void UpdateObject(int delta);
	virtual void Render();
};
