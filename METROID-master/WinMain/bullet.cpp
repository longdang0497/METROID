#include "bullet.h"

Bullet::Bullet()
{
	bullet = NULL;
	timer = new Timer();
}

Bullet::~Bullet()
{
	delete bullet;
}

void Bullet::SetX(float value)
{
	_x = value;
}

float Bullet::GetX()
{
	return _x;
}

void Bullet::SetY(float value)
{
	_y = value;
}

float Bullet::GetY()
{
	return _y;
}

void Bullet::SetVx(float value)
{
	_vx = value;
}

float Bullet::GetVx()
{
	return _vx;
}

void Bullet::CreateBullet(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	bullet = new Sprite(_SpriteHandler, METROID_EFFECT, BULLET, BULLET_WIDTH, BULLET_HEIGHT, BULLET_COUNT, SPRITE_PER_ROW);
	//_vx = 0;
	//_vy = 0;
}

void Bullet::RenderBullet()
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//int vpx = 0;
	bullet->Render(_x, _y, _vx, VIEW_PORT_Y);
	_SpriteHandler->End();
}

void Bullet::MoveRight(int Delta)
{
	//move bullet to right
	_x = (_vx + 10) * Delta;
}

void Bullet::MoveLeft(int Delta)
{
	//move bullet to the left
	_x = (_vx - 10) * Delta;
}

void Bullet::UpdateCollison(GameObject * _simon, vector<GameObject*>, Game *, float)
{
}




