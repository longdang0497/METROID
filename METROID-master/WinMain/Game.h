#pragma once
#include <windows.h>
#include <d3d9.h>
#include <dinput.h>
#include "Camera.h"
#include "Samus.h"

#define KEY_DOWN(code) ( IsKeyDown(code) )

#define KEYBOARD_BUFFER_SIZE	1024

class Game
{
protected:
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddv;		// Rendering device
	LPDIRECT3DSURFACE9 _BackBuffer;	// Pointer to backbuffer 
	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer
	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 

	//Camera *cam;
	HINSTANCE _hInstance;	// Handle of the game instance
	HWND _hWnd;				// Handle of the Game Window
	LPWSTR _Name;			// Name of game will be used as Window Class Name

	// Buffered keyboard data
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];

	int _FrameRate;
	int _IsFullScreen;		// Is running in fullscreen mode?
	int _Mode;				// Screen mode 
	int _ScreenWidth;
	int _ScreenHeight;
	int _Depth;

	DWORD _DeltaTime;		// Time between the last frame and current frame
	D3DFORMAT _BackBufferFormat;

	int _ViewPortWidth;		// Height of view port
	int _ViewPortHeight;	// Width of view port

	int _ViewPortX;			// Position of view port in World space
	int _ViewPortY;
public:
	Game(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullscreen, int FrameRate);
	~Game();
	void _SetScreenDimension(int Mode);
	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	LPDIRECT3DDEVICE9 getdevice();
	void setdevice(LPDIRECT3DDEVICE9 d3ddv);

	void _InitWindow();
	void _InitDirectX();
	void _InitKeyboard();

	void _ProcessKeyBoard();
	int IsKeyDown(int KeyCode);

	// Render a single frame
	void _RenderFrame();
	virtual void UpdateWorld(int Delta);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ObjectCollision(int Delta);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	// Initialize the game with set parameters
	void Game_Init();

	// Run game
	void Game_Run();
};
