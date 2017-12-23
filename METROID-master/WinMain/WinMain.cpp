#include <windows.h>
#include <time.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "Samus.h"
#include "Game.h"
#include "Metroid.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Metroid g(hInstance, L"METROID GAME", GAME_SCREEN_RESOLUTION_640_480_24, 0, 60);

	g.Game_Init();
	g.Game_Run();

	return 0;
}