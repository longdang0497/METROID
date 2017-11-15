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

