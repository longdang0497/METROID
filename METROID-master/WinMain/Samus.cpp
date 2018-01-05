#include "Samus.h"
#include <d3dx9.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Define.h"

int max_camera_x = 300;
int max_camera_y = 480;

int min_camera_x = 0;
int min_camera_y = 480;

Samus::Samus()
{
	type = typeSAMUS;
	samus_appearing = NULL;
	samus_right = NULL;
	samus_left = NULL;
	samus_aim_up_left = NULL;
	samus_aim_up_right = NULL;
	samus_morph_left = NULL;
	samus_morph_right = NULL;
	samus_idle_aim_up_left = NULL;
	samus_idle_aim_up_right = NULL;
	samus_jump_left = NULL;
	samus_jump_right = NULL;
	samus_idle_left = NULL;
	samus_idle_right = NULL;
	run_shooting_left = NULL;
	run_shooting_right = NULL;
	samus_somersault_left = NULL;
	samus_somersault_right = NULL;
	samus_jumping_shooting_left = NULL;
	samus_jumping_shooting_right = NULL;
	samus_jump_aim_up_left = NULL;
	samus_jump_aim_up_right = NULL;
}

Samus::Samus(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	//Collider
	collider = new Collider();
}

Samus::~Samus()
{
	delete(samus_appearing);
	delete(samus_right);
	delete(samus_left);
	delete(samus_aim_up_left);
	delete(samus_aim_up_right);
	delete(samus_idle_aim_up_left);
	delete(samus_idle_aim_up_right);
	delete(samus_morph_left);
	delete(samus_morph_right);
	delete(run_shooting_left);
	delete(run_shooting_right);
	delete(samus_idle_left);
	delete(samus_idle_right);
	delete(samus_jump_left);
	delete(samus_jump_right);
	delete(samus_somersault_left);
	delete(samus_somersault_right);
	delete(samus_jumping_shooting_left);
	delete(samus_jumping_shooting_right);
	delete(samus_jump_aim_up_left);
	delete(samus_jump_aim_up_right);
}

void Samus::CreateSamus(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;

	//Create instance of sprites
	samus_appearing = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, APPEARING, APPEARING_WIDTH, APPEARING_HEIGHT, APPEARING_COUNT, SPRITE_PER_ROW);
	samus_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUNNING_RIGHT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	samus_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUNNING_LEFT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	samus_jump_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_LEFT, JUMP_WIDTH, JUMP_HEIGHT, JUMP_COUNT, SPRITE_PER_ROW);
	samus_jump_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_RIGHT, JUMP_WIDTH, JUMP_HEIGHT, JUMP_COUNT, SPRITE_PER_ROW);
	samus_idle_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STANDING_LEFT, STANDING_WIDTH, STANDING_HEIGHT, STANDING_COUNT, SPRITE_PER_ROW);
	samus_idle_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STANDING_RIGHT, STANDING_WIDTH, STANDING_HEIGHT, STANDING_COUNT, SPRITE_PER_ROW);
	samus_idle_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, IDLE_AIM_UP_LEFT, IDLE_AIM_UP_WIDTH, IDLE_AIM_UP_HEIGHT, IDLE_AIM_UP_COUNT, SPRITE_PER_ROW);
	samus_idle_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, IDLE_AIM_UP_RIGHT, IDLE_AIM_UP_WIDTH, IDLE_AIM_UP_HEIGHT, IDLE_AIM_UP_COUNT, SPRITE_PER_ROW);
	samus_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_AIM_UP_LEFT, RUN_AIM_UP_WIDTH, RUN_AIM_UP_HEIGHT, RUN_AIM_UP_COUNT, SPRITE_PER_ROW);
	samus_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_AIM_UP_RIGHT, RUN_AIM_UP_WIDTH, RUN_AIM_UP_HEIGHT, RUN_AIM_UP_COUNT, SPRITE_PER_ROW);
	run_shooting_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_SHOOTING_LEFT, RUN_SHOOTING_WIDTH, RUN_SHOOTING_HEIGHT, RUN_SHOOTING_COUNT, SPRITE_PER_ROW);
	run_shooting_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_SHOOTING_RIGHT, RUN_SHOOTING_WIDTH, RUN_SHOOTING_HEIGHT, RUN_SHOOTING_COUNT, SPRITE_PER_ROW);
	samus_morph_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, MORPH_BALL_LEFT, MORPH_BALL_WIDTH, MORPH_BALL_HEIGHT, MORPH_BALL_COUNT, SPRITE_PER_ROW);
	samus_morph_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, MORPH_BALL_RIGHT, MORPH_BALL_WIDTH, MORPH_BALL_HEIGHT, MORPH_BALL_COUNT, SPRITE_PER_ROW);
	samus_somersault_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, _LEFT_SOMERSAULT, SOMERSAULT_WIDTH, SOMERSAULT_HEIGHT, SOMERSAULT_COUNT, SPRITE_PER_ROW);
	samus_somersault_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, _RIGHT_SOMERSAULT, SOMERSAULT_WIDTH, SOMERSAULT_HEIGHT, SOMERSAULT_COUNT, SPRITE_PER_ROW);
	samus_jumping_shooting_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, _LEFT_JUMP_SHOOT, JUMPING_SHOOTING_WIDTH, JUMPING_SHOOTING_HEIGHT, JUMPING_SHOOTING_COUNT, SPRITE_PER_ROW);
	samus_jumping_shooting_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, _RIGHT_JUMP_SHOOT, JUMPING_SHOOTING_WIDTH, JUMPING_SHOOTING_HEIGHT, JUMPING_SHOOTING_COUNT, SPRITE_PER_ROW);
	samus_jump_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, _LEFT_JUMP_SHOOT_AIM_UP, JUMP_AIM_UP_WIDTH, JUMP_AIM_UP_HEIGHT, JUMP_AIM_UP_COUNT, SPRITE_PER_ROW);
	samus_jump_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, _RIGHT_JUMP_SHOOT_AIM_UP, JUMP_AIM_UP_WIDTH, JUMP_AIM_UP_HEIGHT, JUMP_AIM_UP_COUNT, SPRITE_PER_ROW);

	//create initial Samus's position
	_x = 50;
	_y = GROUND_Y;

	_vx = 0;
	_vx_last = 1.0f;
	_vy = 0;

	rigidBody = D3DXVECTOR2(32, 32);

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

//void Samus::UpdateCollison(GameObject * _samus, vector<GameObject*> _list, Game * _input, float)
//{
//	for (int i = 0; i < (int)_list.size(); i++)
//	{
//		switch (_list[i]->GetType())
//		{
//		case typeSpiderBug:
//			if (Collision(_samus->GetRectCollision(), _list[i]->getListChildren()[0]->GetRectCollision()))
//			{
//				_samus->SetX(10);
//			}
//			break;
//		}
//	}
//}

void Samus::Reset(int x, int y)
{
	//set Samus active 
	isActive = true;

	//reset Samus's position
	this->_x = x;
	this->_y = y;
}

void Samus::UpdateObject(float delta)
{
	_x += _vx * delta;
	_y += _vy * delta;

	Camera::SetCameraX(_x);

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case RIGHTING:
			samus_right->Next();
			break;
		case LEFTING:
			samus_left->Next();
			break;
		case AIMING_UP_LEFT:
			samus_aim_up_left->Next();
			break;
		case AIMING_UP_RIGHT:
			samus_aim_up_right->Next();
			break;
		case TRANSFORM_BALL_LEFT:
			samus_morph_left->Next();
			break;
		case TRANSFORM_BALL_RIGHT:
			samus_morph_right->Next();
			break;
		case RUN_SHOOT_LEFT:
			run_shooting_left->Next();
			break;
		case RUN_SHOOT_RIGHT:
			run_shooting_right->Next();
			break;
		case SAMUS_SOMERSAULT_LEFT:
			samus_somersault_left->Next();
			break;
		case SAMUS_SOMERSAULT_RIGHT:
			samus_somersault_right->Next();
			break;
		case JUMPING_SHOOTING_LEFT:
			samus_jumping_shooting_left->Next();
			break;
		case JUMPING_SHOOTING_RIGHT:
			samus_jumping_shooting_right->Next();
			break;
		case JUMPING_AIM_UP_LEFT:
			samus_jump_aim_up_left->Next();
			break;
		case JUMPING_AIM_UP_RIGHT:
			samus_jump_aim_up_right->Next();
			break;
		}
			
		last_time = now;
	}

	//check if Samus stays on ground or not
	if (_y > GROUND_Y) _vy -= FALLDOWN_VELOCITY_DECREASE;
	else
	{
		_y = GROUND_Y;
		_vy = 0;
		if (state == JUMPING_LEFT || state == JUMPING_SHOOTING_LEFT || state == SAMUS_SOMERSAULT_LEFT || state == JUMPING_AIM_UP_LEFT)
		{
			state = IDLE_LEFT;
		}
		else if (state == JUMPING_RIGHT || state == JUMPING_SHOOTING_RIGHT || state == SAMUS_SOMERSAULT_RIGHT || state == JUMPING_AIM_UP_RIGHT)
		{
			state = IDLE_RIGHT;
		}
	}
}

void Samus::UnActiveObject()
{
	isActive = false;	//set Samus out of viewport
}

void Samus::Render()
{
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	switch (state)
	{
	case RIGHTING:
		samus_right->Render(_x, _y);
		break;
	case LEFTING:
		samus_left->Render(_x, _y);
		break;
	case AIMING_UP_LEFT:
		samus_aim_up_left->Render(_x, _y);
		break;
	case AIMING_UP_RIGHT:
		samus_aim_up_right->Render(_x, _y);
		break;
	case IDLING_AIM_UP_LEFT:
		samus_idle_aim_up_left->Render(_x, _y);
		break;
	case IDLING_AIM_UP_RIGHT:
		samus_idle_aim_up_right->Render(_x, _y);
		break;
	case IDLE_LEFT:
		samus_idle_left->Render(_x, _y);
		break;
	case IDLE_RIGHT:
		samus_idle_right->Render(_x, _y);
		break;
	case JUMPING_LEFT:
		samus_jump_left->Render(_x, _y);
		break;
	case JUMPING_RIGHT:
		samus_jump_right->Render(_x, _y);
		break;
	case TRANSFORM_BALL_LEFT:
		samus_morph_left->Render(_x, _y);
		break;
	case TRANSFORM_BALL_RIGHT:
		samus_morph_right->Render(_x, _y);
		break;
	case RUN_SHOOT_LEFT:
		run_shooting_left->Render(_x, _y);
		break;
	case RUN_SHOOT_RIGHT:
		run_shooting_right->Render(_x, _y);
		break;
	case SAMUS_SOMERSAULT_LEFT:
		samus_somersault_left->Render(_x, _y);
		break;
	case SAMUS_SOMERSAULT_RIGHT:
		samus_somersault_right->Render(_x, _y);
		break;
	case JUMPING_SHOOTING_LEFT:
		samus_jumping_shooting_left->Render(_x, _y);
		break;
	case JUMPING_SHOOTING_RIGHT:
		samus_jumping_shooting_right->Render(_x, _y);
	case JUMPING_AIM_UP_LEFT:
		samus_jump_aim_up_left->Render(_x, _y);
		break;
	case JUMPING_AIM_UP_RIGHT:
		samus_jump_aim_up_right->Render(_x, _y);
		break;
	}
	spriteHandler->End();
}

void Samus::SpriteReset()
{
	samus_appearing->Reset();
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
	samus_morph_left->Reset();
	samus_morph_right->Reset();
	samus_somersault_left->Reset();
	samus_somersault_right->Reset();
	samus_jumping_shooting_left->Reset();
	samus_jumping_shooting_right->Reset();
	samus_jump_aim_up_left->Reset();
	samus_jump_aim_up_right->Reset();
}







