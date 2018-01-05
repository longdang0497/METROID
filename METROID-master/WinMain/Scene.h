#pragma once
#include <d3dx9.h>

class Scene
{
public: 
	Scene();
	~Scene();

	virtual void UpdateWorld(float Delta);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void OnKeyDown(int KeyCode);
	virtual void Release();
};
