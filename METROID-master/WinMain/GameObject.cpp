#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(int X, int Y, float Vx, float Vy)
{
	_x = X;
	_y = Y;
	_vx = Vx;
	_vy = Vy;
}

GameObject::~GameObject()
{
}

void GameObject::SetRECT(RECT value)
{
}

RECT GameObject::GetRECT()
{
	return RECT();
}

void GameObject::SetX(float value)
{
	_x = value;
}

float GameObject::GetX()
{
	return _x;
}

void GameObject::SetY(float value)
{
	_y = value;
}

float GameObject::GetY()
{
	return _y;
}

void GameObject::SetVx(float value)
{
	_vx = value;
}

float GameObject::GetVx()
{
	return _vx;
}

void GameObject::SetVy(float value)
{
	_vy = value;
}

float GameObject::GetVy()
{
	return _vy;
}

void GameObject::SetVelocityXLast(float value)
{
	_vx_last = value;
}

float GameObject::GetVelocityXLast()
{
	return _vx_last;
}

void GameObject::SetWidth(int value)
{
	_width = value;
}

int GameObject::GetWidth()
{
	return _width;
}

void GameObject::SetHeight(int value)
{
	_height = value;
}

int GameObject::GetHeight()
{
	return _height;
}

void GameObject::UpdateObject(int delta)
{
}

void GameObject::Render()
{
}

//void GameObject::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
//{
//	/*switch (state)
//	{
//	case RIGHTING:
//	samus_right->Render(_x, _y, vpx, VIEW_PORT_Y);
//	break;
//	case LEFTING:
//	samus_left->Render(_x, _y, vpx, VIEW_PORT_Y);
//	break;
//	}*/
//
//	//
//	//  Select correct sprite to render depends on which direction mario is facing
//	//
//
//	//samus_appearing->Render(_x, _y, vpx, VIEW_PORT_Y);
//	
//}

