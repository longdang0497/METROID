#include "bullet.h"

Bullet::Bullet(LPDIRECT3DDEVICE9* d3ddv, float X, float Y, float VX, float VY)
{
	bullet = NULL;
	timer = new Timer();
	isRender = false;
	m_d3ddv = d3ddv;
	CreateBullet();

	_x = X;
	_y = Y;

	_vx = VX;
	_vy = VY;
}

Bullet::~Bullet()
{
	if (m_d3ddv) { bullet = nullptr; delete m_d3ddv; };
	if (bullet) { bullet = nullptr;	delete bullet; };
}

void Bullet::SetState(BulletDirection value)
{
	bulletdir = value;
}

BulletDirection Bullet::GetState()
{
	return bulletdir;
}

void Bullet::CreateBullet()
{
	if (m_d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(*m_d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	bullet = new Sprite(_SpriteHandler, BULLET_PATH, BULLET, BULLET_WIDTH, BULLET_HEIGHT, BULLET_COUNT, SPRITE_PER_ROW);
}

void Bullet::UpdateObject(float Delta)
{
	_x += _vx*Delta;
	_y += _vy*Delta;
	Render();
}

void Bullet::Render()
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//float vpx = 0;
	bullet->Render(_x, _y);
	_SpriteHandler->End();
	isRender = true;
}

bool Bullet::isRendering()
{
	Render();
	if (!isRender) return false;
	else
		return true;
}

//void Bullet::UpdateCollison(GameObject * _simon, vector<GameObject*>, Game *, float)
//{
//}




