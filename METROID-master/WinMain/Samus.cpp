#include "Samus.h"
#include <d3dx9.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Define.h"

Samus::Samus()
{
	//samus_appearing = NULL;
	samus_right = NULL;
	samus_left = NULL;

	mLeftDeviation = 0;
	mRightDeviation = 0;
	mTopDeviation = 0;
	mBottonDeviation = 0;
}

Samus::~Samus()
{
	delete(samus_appearing);
	delete(samus_right);
	delete(samus_left);
}

void Samus::CreateSamus(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create instance of sprites
	samus_appearing = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, APPEARING, APPEARING_WIDTH, APPEARING_HEIGHT, APPEARING_COUNT, SPRITE_PER_ROW);
	samus_right = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUNNING_RIGHT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	samus_left = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUNNING_LEFT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	samus_jump_left = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, JUMP_LEFT, JUMP_WIDTH, JUMP_HEIGHT, JUMP_COUNT, SPRITE_PER_ROW);
	samus_jump_right = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, JUMP_RIGHT, JUMP_WIDTH, JUMP_HEIGHT, JUMP_COUNT, SPRITE_PER_ROW);
	samus_idle_left = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, STANDING_LEFT, STANDING_WIDTH, STANDING_HEIGHT, STANDING_COUNT, SPRITE_PER_ROW);
	samus_idle_right = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, STANDING_RIGHT, STANDING_WIDTH, STANDING_HEIGHT, STANDING_COUNT, SPRITE_PER_ROW);
	samus_idle_aim_up_left = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, IDLE_AIM_UP_LEFT, IDLE_AIM_UP_WIDTH, IDLE_AIM_UP_HEIGHT, IDLE_AIM_UP_COUNT, SPRITE_PER_ROW);
	samus_idle_aim_up_right = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, IDLE_AIM_UP_RIGHT, IDLE_AIM_UP_WIDTH, IDLE_AIM_UP_HEIGHT, IDLE_AIM_UP_COUNT, SPRITE_PER_ROW);
	samus_aim_up_left = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUN_AIM_UP_LEFT, RUN_AIM_UP_WIDTH, RUN_AIM_UP_HEIGHT, RUN_AIM_UP_COUNT, SPRITE_PER_ROW);
	samus_aim_up_right = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUN_AIM_UP_RIGHT, RUN_AIM_UP_WIDTH, RUN_AIM_UP_HEIGHT, RUN_AIM_UP_COUNT, SPRITE_PER_ROW);
	run_shooting_left = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUN_SHOOTING_LEFT, RUN_SHOOTING_WIDTH, RUN_SHOOTING_HEIGHT, RUN_SHOOTING_COUNT, SPRITE_PER_ROW);
	run_shooting_right = new Sprite(_SpriteHandler, SAMUS_SPRITES_PATH, RUN_SHOOTING_RIGHT, RUN_SHOOTING_WIDTH, RUN_SHOOTING_HEIGHT, RUN_SHOOTING_COUNT, SPRITE_PER_ROW);

	_x = 50;
	_y = GROUND_Y;

	_vx = 0;
	_vx_last = 1.0f;
	_vy = 0;

	rigidBody = D3DXVECTOR2(20, 20);

	//Init state of samus
	state = IDLE_RIGHT;
}

SamusStates Samus::GetState()
{
	return state;
}

void Samus::SetState(SamusStates value)
{
	state = value;
}

void Samus::UpdateCollison(GameObject * _samus, vector<GameObject*> _list, Game * _input, float)
{
	for (int i = 0; i < (int)_list.size(); i++)
	{
		switch (_list[i]->GetType())
		{
		case typeSpiderBug:
			if (Collision(_samus->GetRectCollision(), _list[i]->getListChildren()[0]->GetRectCollision()))
			{
				_samus->SetX(10);
			}
			break;
		}
	}
}

void Samus::UpdateObject(int delta)
{
	srand((unsigned)time(NULL));
	_x += _vx * delta;
	_y += _vy * delta;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (_vx > 0) samus_right->Next();
		if (_vx < 0) samus_left->Next();
		last_time = now;
	}
	RenderSpriteSamus();

	if (_y > GROUND_Y) _vy -= FALLDOWN_VELOCITY_DECREASE;
	else
	{
		_y = GROUND_Y;
		_vy = 0;
	}
}

void Samus::Update()
{
	//UpdateCollison(_samus, _list, _input, time);
}

int xc = 0;

void Samus::RenderSpriteSamus()
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//int vpx = _x - 400;
	//int vpx = xc;
	//if (vpx <= 0) vpx = 0;
	//xc += 1;
	int vpx = 0;
	switch (state)
	{
	case RIGHTING:
		samus_right->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case LEFTING:
		samus_left->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case AIMING_UP_LEFT:
		samus_aim_up_left->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case AIMING_UP_RIGHT:
		samus_aim_up_right->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case IDLING_AIM_UP_LEFT:
		samus_idle_aim_up_left->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case IDLING_AIM_UP_RIGHT:
		samus_idle_aim_up_right->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case IDLE_LEFT:
		samus_idle_left->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case IDLE_RIGHT:
		samus_idle_right->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case JUMPING_LEFT:
		samus_jump_left->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	case JUMPING_RIGHT:
		samus_jump_right->Render(_x, _y, vpx, VIEW_PORT_Y);
		break;
	}
	_SpriteHandler->End();
}

void Samus::SpriteReset()
{
	//samus_appearing->Reset();
	samus_left->Reset();
	samus_right->Reset();
	samus_jump_left->Reset();
	samus_jump_right->Reset();
	samus_aim_up_left->Reset();
	samus_aim_up_right->Reset();
	samus_idle_aim_up_left->Reset();
	samus_idle_aim_up_right->Reset();
	samus_idle_left->Reset();
	samus_idle_right->Reset();
	run_shooting_left->Reset();
	run_shooting_right->Reset();
}







