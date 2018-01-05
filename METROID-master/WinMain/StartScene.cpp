#include "StartScene.h"

StartScene::StartScene(LPD3DXSPRITE spriteHandle)
{
	_background = new Sprite(spriteHandle, INTRO_SCENE, NULL, 256, 240, 1, 1);
	_sound = new GameSound();
	_isPressed = true;
}

StartScene::~StartScene()
{
}

void StartScene::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_SPACE)
	{
		_isPressed = true;
	}
}

//bool StartScene::init()
//{
//	/*bool check = _sound->Init(_hWnd);
//	if (!check)
//	{
//		MessageBox(_hWnd, L"Error initialize sound !", L"Error", MB_OK);
//	}
//	_sound->LoadSound(APPEARING_SOUND);
//	CSound * audio = _sound->LoadSound(APPEARING_SOUND);
//	if (audio == NULL) return;
//	_sound->Playsound(audio);*/
//	return true;
//}

//void StartScene::draw(LPD3DXSPRITE spriteHandle)
//{
//	_background->Render(0, 0);
//}
