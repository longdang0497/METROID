#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Sound.h"
#include "Define.h"
#include <dinput.h>

class StartScene : public Scene
{
private:
	Sprite * _background;
	GameSound * _sound;
	bool _isPressed;
public:
	StartScene(LPD3DXSPRITE spriteHandle);
	~StartScene();

	/*virtual void UpdateWorld(float Delta);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);*/
	virtual void OnKeyDown(int KeyCode);
};
