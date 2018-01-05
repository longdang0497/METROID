#pragma once
#include <windows.h>
#include <DxErr.h>
#include "Samus.h"
#include "Sound.h"
#include "Define.h"
#include "Input.h"
#include "DXGraphics.h"
#include "DeviceManager.h"

class Game
{
protected:
	DWORD _DeltaTime;		// Time between the last frame and current frame
	Input * _input;
	static Graphics * _dxgraphics;
	DeviceManager * _device;
public:
	Game();
	Game(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullscreen, float FrameRate);
	~Game();


	// Render a single frame
	void _RenderFrame();
	virtual void UpdateWorld(float Delta);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	// Initialize the game with set parameters
	void Game_Init();

	// Run game
	void Game_Run();
};
