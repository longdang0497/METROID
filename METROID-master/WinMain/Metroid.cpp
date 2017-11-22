#include "Metroid.h"
#include <limits>
#include <algorithm>

Metroid::Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate)	 : 
	Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	_Background = NULL;
	samus = new Samus();
	bat = new FlyingBat();
	spider = new SpiderBug();
	bullet = new Bullet();
	timer = new Timer();
}

Metroid::~Metroid()
{
	delete samus;
	delete bat;
	delete spider;
	delete bullet;
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

bool Metroid::CheckCollision(Samus *a, SpiderBug *b)
{
	RECT rec_a = a->getRECTSamus();
	RECT rec_b = b->getRECTSpider();

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

	if (first_case || second_case || third_case || fourth_case) return true;

	return false;
}

float Metroid::SweptAABB(GameObject * a, GameObject * b, float & normalX, float & normalY)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (a->GetVx() > 0.0f)
	{
		xInvEntry = b->GetX() - (a->GetX() + a->GetWidth());
		xInvExit = (b->GetX() + b->GetWidth()) - a->GetX();
	}
	else
	{
		xInvEntry = (b->GetX() + b->GetWidth()) - a->GetX(); 
		xInvExit = b->GetX() - (a->GetX() + a->GetWidth());
	}

	if (b->GetVy() > 0.0f)
	{
		yInvEntry = b->GetY() - (a->GetY() + a->GetHeight());
		yInvExit = (b->GetY() + b->GetHeight()) - a->GetY();
	}
	else
	{
		yInvEntry = (b->GetY() + b->GetHeight()) - a->GetY();
		yInvExit = b->GetY() - (a->GetY() + a->GetHeight());
	}

	//find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (a->GetVx() == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / a->GetVx();
		xExit = xInvExit / a->GetVx();
	}

	if (a->GetVy() == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / a->GetVy();
		yExit = yInvExit / a->GetVy();
	}

	//find the earliest and latest time of collision 
	float entryTime = (std::max)(xEntry, yEntry);
	float exitTime = (std::min)(xExit, yExit);

	//if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalX = 0.0f;
		normalY = 0.0f;
		return 1.0f;
	}
	else //if there was collision
	{
		//calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry  < 0.0f)
			{
				normalX = 1.0f;
				normalY = 0.0f;
			}
			else
			{
				normalX = -1.0f;
				normalY = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalX = 0.0f;
				normalY = 1.0f;
			}
			else
			{
				normalX = 0.0f;
				normalY = 1.0f;
			}
		}
		//return the time of collision
		return entryTime;
	}
}

void Metroid::ObjectCollision(int Delta)
{
	bool check = CheckCollision(samus, spider);
	//if (check != false || samus->GetX() == spider->GetX())
	{
		//spider->SetX(spider->GetVx() * Delta);
		//spider->SetVy(0.05);
		//MessageBox(NULL, L"Collided !!!", NULL, NULL);
	}
	if (spider->GetX() == 0) spider->SetVx(-spider->GetVx());
}

void Metroid::UpdateWorld(int Delta)
{
}

void Metroid::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	d3ddv->StretchRect(
		_Background,			// from
		NULL,				// which portion?
		_BackBuffer,		// to
		NULL,				// which portion?
		D3DTEXF_NONE);
	samus->UpdateObject(Delta);
	bat->UpdateObject(Delta);
	spider->UpdateObject(Delta);
}

void Metroid::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	if (IsKeyDown(DIK_RIGHT))
	{
		samus->SetVelocityX(SAMUS_SPEED);
		samus->SetVelocityXLast(samus->GetVelocityX());
		samus->SetState(RIGHTING);
		if (IsKeyDown(DIK_UP)) samus->SetState(JUMPING_RIGHT);
	}
	else if (IsKeyDown(DIK_LEFT))
		{
			samus->SetVelocityX(-SAMUS_SPEED);
			samus->SetVelocityXLast(samus->GetVelocityX());
			samus->SetState(LEFTING);
			if (IsKeyDown(DIK_UP)) samus->SetState(JUMPING_LEFT);
		}
		else if (IsKeyDown(DIK_UP) && samus->GetState() == IDLE_RIGHT)
		{
			samus->SetState(JUMPING_RIGHT);
		}
		else if (IsKeyDown(DIK_UP) && samus->GetState() == IDLE_LEFT)
		{
			samus->SetState(JUMPING_LEFT);
		}
		else
		{
			if (samus->GetVelocityXLast() > 0)
			{
				samus->SetVelocityX(0);
				samus->SetState(IDLE_RIGHT);
			}
			else
			{
				samus->SetVelocityX(0);
				samus->SetState(IDLE_LEFT);
			}
			samus->SpriteReset();
		}
	if (IsKeyDown(DIK_SPACE))
	{
		bullet->SetY(samus->GetY());
		bullet->SetX(samus->GetX());
		bullet->RenderBullet();
		bullet->SetVx(BULLET_SPEED);
		
		switch (samus->GetState())
		{
		case RIGHTING:
			return bullet->MoveRight(Delta);
			break;
		case LEFTING:
			return bullet->MoveLeft(Delta);
			break;
		case AIMING_UP_LEFT:
			return bullet->MoveLeft(Delta);
			break;
		case AIMING_UP_RIGHT:
			return bullet->MoveRight(Delta);
			break;
		case IDLING_AIM_UP_LEFT:
			return bullet->MoveLeft(Delta);
			break;
		case IDLING_AIM_UP_RIGHT:
			return bullet->MoveRight(Delta);
			break;
		case IDLE_LEFT:
			return bullet->MoveLeft(Delta);
			break;
		case IDLE_RIGHT:
			return bullet->MoveRight(Delta);
			break;
		case JUMPING_LEFT:
			return bullet->MoveLeft(Delta);
			break;
		case JUMPING_RIGHT:
			return bullet->MoveRight(Delta);
			break;
		}
	}
}

void Metroid::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	_Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	samus->CreateSamus(d3ddv);
	bat->CreateBat(d3ddv);
	spider->CreateSpiderBug(d3ddv);
	bullet->CreateBullet(d3ddv);
}

void Metroid::OnKeyDown(int KeyCode)
{
	int _y = samus->GetY();
	switch (KeyCode)
	{
	case DIK_UP:
		if (_y <= GROUND_Y)
		{
			int Vy = samus->GetVelocityY();
  			Vy += JUMP_VELOCITY_BOOST;			// start jump if is not "on-air"
			samus->SetVelocityY(Vy);
		}
		break;
	/*case DIK_SPACE:
		
		break;*/
	}
}
