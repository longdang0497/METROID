#include "Metroid.h"

Metroid::Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) : 
	Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	_Background = NULL;
	samus = new Samus();
	bat = new FlyingBat();
	spider = new SpiderBug();
}

Metroid::~Metroid()
{
	delete(samus);
	delete(bat);
	delete(spider);
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
	}
	else
		if (IsKeyDown(DIK_LEFT))
		{
			samus->SetVelocityX(-SAMUS_SPEED);
			samus->SetVelocityXLast(samus->GetVelocityX());
			samus->SetState(LEFTING);
		}
		else
		{
			samus->SetVelocityX(0);
			samus->SpriteReset();
		}
}

void Metroid::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	_Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	samus->CreateSamus(d3ddv);
	bat->CreateBat(d3ddv);
	spider->CreateSpiderBug(d3ddv);
}

void Metroid::OnKeyDown(int KeyCode)
{
	int _y = samus->GetY();
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (_y <= GROUND_Y)
		{
			float Vy = samus->GetVelocityY();
  			Vy += JUMP_VELOCITY_BOOST;			// start jump if is not "on-air"
			samus->SetVelocityY(Vy);
		}
		break;
	}
}
