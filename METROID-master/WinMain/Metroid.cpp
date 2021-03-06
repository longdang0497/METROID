﻿#include "Metroid.h"
#include <limits>
#include <algorithm>

Metroid::Metroid()
{
}

Metroid::Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, float FrameRate)	 :
	Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	obj = new GameObject();
	//game = new Game(hInstance, Name, Mode, IsFullScreen, FrameRate);
	_Background = NULL;
	//rock = new GroundRock();
	start_shoot = 0;
	tick_per_frame = 1000 / FrameRate;

	timer = new Timer();
	sound = new GameSound();
}

Metroid::~Metroid()
{
	delete world->samus;
	delete world->bat;
	//delete world->spider;
}

LPDIRECT3DSURFACE9 Metroid::CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath)
{
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(NULL, L"[ERROR] Failed to get image info.", NULL, NULL);
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;

	d3ddv->CreateOffscreenPlainSurface(
		info.Width,				// width
		info.Height,			// height
		D3DFMT_X8R8G8B8,		// format
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	result = D3DXLoadSurfaceFromFile(
		surface, 		// surface
		NULL,			// destination palette	
		NULL,			// destination rectangle 
		FilePath,
		NULL,			// source rectangle
		D3DX_DEFAULT, 	// filter image
		D3DCOLOR_XRGB(0, 0, 0),				// transparency (0 = none)
		NULL);			// reserved

	if (result != D3D_OK)
	{
		MessageBox(NULL, L"[ERROR] D3DXLoadSurfaceFromFile() failed", NULL, NULL);
		return NULL;
	}

	return surface;
}

void Metroid::ShootBullet(BulletDirection bullDir)
{
	now_shoot = GetTickCount();
	if (start_shoot <= 0) //if shooting is active
	{
		start_shoot = GetTickCount();
		//bulletManager->Next(dir);
	}
	else if ((now_shoot - start_shoot) > BULLET_SPEED * tick_per_frame)
	{
		//Reset start_shoot
		start_shoot = 0;
	}
	Sleep(now_shoot - start_shoot);
}

bool Metroid::CheckCollision(RECT a, RECT b)
{
	RECT rec_a = a;
	RECT rec_b = b;

	bool top = rec_a.top <= rec_b.top && rec_a.top >= rec_b.bottom;
	bool bot = rec_a.bottom <= rec_b.top && rec_a.bottom >= rec_b.bottom;
	bool right = rec_a.right <= rec_b.right && rec_a.right >= rec_b.left;
	bool left = rec_a.left <= rec_b.right && rec_a.left >= rec_b.left;

	bool first_case = (left && bot) || (left && top);
	bool second_case = (right && bot) || (right && top);

	bool third_caseA = left && (rec_a.bottom <= rec_b.bottom) && (rec_a.top >= rec_b.top);
	bool third_caseB = right && (rec_a.bottom <= rec_b.bottom) && (rec_a.top >= rec_b.top);
	bool third_case = third_caseA || third_caseB;

	bool fourth_caseA = top && (rec_a.left >= rec_b.left) && (rec_a.right <= rec_b.right);
	bool fourth_caseB = bot && (rec_a.left >= rec_b.left) && (rec_a.right <= rec_b.right);
	bool fourth_case = fourth_caseA || fourth_caseB;

	if (first_case || second_case || third_case || fourth_case) 
		return true;

	return false;
}

void Metroid::UpdateWorld(float Delta)
{
	
	//obj->Update();
	manager->UpdateObject(Delta);	
	world->Update(Delta);
}

void Metroid::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
	d3ddv->StretchRect(
		_Background,			// from
		NULL,				// which portion?
		_device->getBuffer(),		// to
		NULL,				// which portion?
		D3DTEXF_NONE);
	for (int i = 0; i < Player.size(); i++)
	{
		Player[i]->UpdateObject(Delta);
	}
	world->Render();
	manager->Render();
	//rock->Render();
}

void Metroid::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
	if (_input->IsKeyDown(DIK_RIGHT))
	{
		//world->samus->setDirection(DirectCollision::LEFT);
		world->samus->SetVelocityXLast(world->samus->GetVx());
		world->samus->SetVx(SAMUS_SPEED);
		if (world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT
			&& world->samus->GetState() != JUMPING_LEFT && world->samus->GetState() != JUMPING_RIGHT
			&& world->samus->GetState() != JUMPING_SHOOTING_LEFT && world->samus->GetState() != JUMPING_SHOOTING_RIGHT
			&& world->samus->GetState() != SAMUS_SOMERSAULT_LEFT)
		{
			if (_input->IsKeyDown(DIK_X))
			{
				if (world->samus->GetState() != SAMUS_SOMERSAULT_RIGHT)
				{
					start_jump = GetTickCount();
					now_jump = GetTickCount();
					world->samus->SetState(SAMUS_SOMERSAULT_RIGHT);
					world->samus->SetVy(world->samus->GetVy() - JUMP_VELOCITY_BOOST_FIRST);
				}
				else
				{
					now_jump = GetTickCount();
					if ((now_jump - start_jump) <= 20 * tick_per_frame)
					{
						world->samus->SetVy(world->samus->GetVy() + JUMP_VELOCITY_BOOST);
					}
				}
			}
			else if (world->samus->GetState() != SAMUS_SOMERSAULT_RIGHT)
				world->samus->SetState(RIGHTING);
		}
	}
	else if (_input->IsKeyDown(DIK_LEFT))
	{
		//world->samus->setDirection(DirectCollision::RIGHT);
		world->samus->SetVelocityXLast(world->samus->GetVx());
		world->samus->SetVx(-SAMUS_SPEED);
		if (world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT
			&& world->samus->GetState() != JUMPING_LEFT && world->samus->GetState() != JUMPING_RIGHT
			&& world->samus->GetState() != JUMPING_SHOOTING_LEFT && world->samus->GetState() != JUMPING_SHOOTING_RIGHT
			&& world->samus->GetState() != SAMUS_SOMERSAULT_RIGHT)
		{
			if (_input->IsKeyDown(DIK_X))
			{
				if (world->samus->GetState() != SAMUS_SOMERSAULT_LEFT)
				{
					start_jump = GetTickCount();
					now_jump = GetTickCount();
					world->samus->SetState(SAMUS_SOMERSAULT_LEFT);
					world->samus->SetVy(world->samus->GetVy() + JUMP_VELOCITY_BOOST_FIRST);
				}
				else
				{
					now_jump = GetTickCount();
					if ((now_jump - start_jump) <= 20 * tick_per_frame)
					{
						world->samus->SetVy(world->samus->GetVy() + JUMP_VELOCITY_BOOST);
					}
				}
			}
			else if (world->samus->GetState() != SAMUS_SOMERSAULT_LEFT)
				world->samus->SetState(LEFTING);
		}
	}
	else if (_input->IsKeyDown(DIK_X))
	{
		//world->samus->setDirection(DirectCollision::DOWN);
		if (world->samus->GetVelocityXLast() < 0)
		{
			if (world->samus->GetState() != JUMPING_LEFT && world->samus->GetState() != SAMUS_SOMERSAULT_LEFT
				&& world->samus->GetState() != JUMPING_SHOOTING_LEFT && world->samus->GetState() != JUMPING_AIM_UP_LEFT)
			{
				start_jump = GetTickCount();
				now_jump = GetTickCount();
				if (world->samus->GetState() == IDLING_AIM_UP_LEFT)
					world->samus->SetState(JUMPING_AIM_UP_LEFT);
				else
					world->samus->SetState(JUMPING_LEFT);
				world->samus->SetVy(world->samus->GetVy() + JUMP_VELOCITY_BOOST_FIRST);
			}
			else
			{
				now_jump = GetTickCount();
				if ((now_jump - start_jump) <= 200 * tick_per_frame)
				{
					world->samus->SetVy(world->samus->GetVy() + JUMP_VELOCITY_BOOST);
				}
			}
		}
		if (world->samus->GetVelocityXLast() > 0)
		{
			if (world->samus->GetState() != JUMPING_RIGHT && world->samus->GetState() != SAMUS_SOMERSAULT_RIGHT
				&& world->samus->GetState() != JUMPING_SHOOTING_RIGHT && world->samus->GetState() != JUMPING_AIM_UP_RIGHT)
			{
				start_jump = GetTickCount();
				now_jump = GetTickCount();
				if (world->samus->GetState() == IDLING_AIM_UP_RIGHT)
					world->samus->SetState(JUMPING_AIM_UP_RIGHT);
				else
					world->samus->SetState(JUMPING_RIGHT);
				world->samus->SetVy(world->samus->GetVy() + JUMP_VELOCITY_BOOST_FIRST);
			}
			else
			{
				now_jump = GetTickCount();
				if ((now_jump - start_jump) <= 20 * tick_per_frame)
				{
					world->samus->SetVy(world->samus->GetVy() + JUMP_VELOCITY_BOOST);

				}
			}
		}
	}
	else
	{
		world->samus->SetVx(0);

		if (world->samus->GetVelocityXLast() < 0)
		{
			if (world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != JUMPING_LEFT && world->samus->GetState() != JUMPING_RIGHT
				&& world->samus->GetState() != JUMPING_SHOOTING_LEFT && world->samus->GetState() != JUMPING_SHOOTING_RIGHT
				&& world->samus->GetState() != SAMUS_SOMERSAULT_LEFT && world->samus->GetState() != SAMUS_SOMERSAULT_RIGHT
				&& world->samus->GetState() != JUMPING_AIM_UP_LEFT)
			{
				world->samus->SetState(IDLE_LEFT);
				world->samus->SpriteReset();
			}
		}
		else
		{
			if (world->samus->GetState() != TRANSFORM_BALL_RIGHT && world->samus->GetState() != JUMPING_LEFT && world->samus->GetState() != JUMPING_RIGHT
				&& world->samus->GetState() != JUMPING_SHOOTING_LEFT && world->samus->GetState() != JUMPING_SHOOTING_RIGHT
				&& world->samus->GetState() != SAMUS_SOMERSAULT_LEFT && world->samus->GetState() != SAMUS_SOMERSAULT_RIGHT
				&& world->samus->GetState() != JUMPING_AIM_UP_RIGHT)
			{
				world->samus->SetState(IDLE_RIGHT);
				world->samus->SpriteReset();
			}
		}
	}

	if (_input->IsKeyDown(DIK_UP))
	{
		if (world->samus->GetState() == LEFTING)
			world->samus->SetState(AIMING_UP_LEFT);
		if (world->samus->GetState() == RIGHTING)
			world->samus->SetState(AIMING_UP_RIGHT);
		if (world->samus->GetState() == IDLE_LEFT)
			world->samus->SetState(IDLING_AIM_UP_LEFT);
		if (world->samus->GetState() == IDLE_RIGHT)
			world->samus->SetState(IDLING_AIM_UP_RIGHT);
		if (world->samus->GetState() == JUMPING_LEFT/* || world->samus->GetState() == ON_JUMPING_SHOOTING_LEFT*/)
			world->samus->SetState(JUMPING_AIM_UP_LEFT);
		if (world->samus->GetState() == JUMPING_RIGHT/* || world->samus->GetState() == ON_JUMPING_SHOOTING_RIGHT*/)
			world->samus->SetState(JUMPING_AIM_UP_RIGHT);

		if (world->samus->GetState() == TRANSFORM_BALL_LEFT)
			world->samus->SetState(IDLE_LEFT);
		if (world->samus->GetState() == TRANSFORM_BALL_RIGHT)
			world->samus->SetState(IDLE_RIGHT);
	}

	/*if (_input->IsKeyDown(DIK_Z))
	{
		if (world->samus->GetState() == AIMING_UP_LEFT || world->samus->GetState() == AIMING_UP_RIGHT
			|| world->samus->GetState() == IDLING_AIM_UP_LEFT || world->samus->GetState() == IDLING_AIM_UP_RIGHT
			|| world->samus->GetState() == JUMPING_AIM_UP_LEFT || world->samus->GetState() == JUMPING_AIM_UP_RIGHT)
		{
			ShootBullet(SHOOT_UP);
		}
		if (world->samus->GetState() == JUMPING_LEFT || world->samus->GetState() == SAMUS_SOMERSAULT_LEFT || world->samus->GetState() == JUMPING_SHOOTING_LEFT)
		{
			world->samus->SetState(JUMPING_SHOOTING_LEFT);

			ShootBullet(SHOOT_LEFT);
		}
		if (world->samus->GetState() == JUMPING_RIGHT || world->samus->GetState() == SAMUS_SOMERSAULT_RIGHT || world->samus->GetState() == JUMPING_SHOOTING_RIGHT)
		{
			world->samus->SetState(JUMPING_SHOOTING_RIGHT);

			ShootBullet(SHOOT_RIGHT);
		}
		if (world->samus->GetState() == LEFTING)
		{
			world->samus->SetState(RUN_SHOOT_LEFT);

			ShootBullet(SHOOT_LEFT);
		}
		if (world->samus->GetState() == RIGHTING)
		{
			world->samus->SetState(RUN_SHOOT_RIGHT);

			ShootBullet(SHOOT_RIGHT);
		}
		if (world->samus->GetState() == IDLE_LEFT)
		{
			ShootBullet(SHOOT_LEFT);
		}
		if (world->samus->GetState() == IDLE_RIGHT)
		{
			ShootBullet(SHOOT_RIGHT);
		}
	}*/

	if (_input->IsKeyDown(DIK_SPACE))
	{
		
	}
}

void Metroid::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	_Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	
	//---------Init spriteHandler---------------
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_spriteHandler);
	if (result != D3D_OK) return;

	world = new World(_spriteHandler, this);

	srand((unsigned)time(NULL));
	world->samus->CreateSamus(d3ddv);
	
	//world->bat->CreateBat(d3ddv);
	//world->spider->CreateSpiderBug(d3ddv);
	Player.push_back(world->samus);

	bool check = sound->Init(_dxgraphics->getWnd());
	if (!check)
	{
		MessageBox(_dxgraphics->getWnd(), L"Error initialize sound !", L"Error", MB_OK);
	}
	sound->LoadSound(ROOMA_SOUND);
	CSound * audio = sound->LoadSound(ROOMA_SOUND);
	if (audio == NULL) return;
	sound->Playsound(audio);
	manager = new Manager(d3ddv);
}

void Metroid::OnKeyDown(int KeyCode)
{
	float pos_y = world->samus->GetY();
	float pos_x = world->samus->GetX();
	switch (KeyCode)
	{
	case DIK_UP:
		if (pos_y <= GROUND_Y)
		{
			float Vy = world->samus->GetVy();
  			Vy += JUMP_VELOCITY_BOOST;			// start jump if is not "on-air"
			world->samus->SetVy(Vy);
		}
		//DWORD now = GetTickCount();
		/*if (now - last_time > 1000 / ANIMATE_RATE)
		{
			
			last_time = now;
		}*/
		break;
	case DIK_SPACE:
		float x = pos_x - 5;
		float y = pos_y + 6;
		if (world->samus->GetVx() > 0) manager->_CreateBullets(x, y, 0.2, 0);
		else /*if (world->samus->GetVx() < 0)*/ manager->_CreateBullets(x, y, -0.2, 0);
		/*if (samus->GetState() == AIMING_UP_LEFT || samus->GetState() == AIMING_UP_RIGHT || samus->GetState() == IDLING_AIM_UP_LEFT ||
			samus->GetState() == IDLING_AIM_UP_RIGHT) manager->_CreateBullets(x, y, 0, 0.2);*/
		break;

	//case DIK_DOWN:
	}
}
