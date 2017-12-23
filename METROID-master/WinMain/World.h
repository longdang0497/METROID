#pragma once
#include <d3dx9.h>
class Samus;
class FlyingBat;
class SpiderBug;
class Metroid;

class World
{
public:
	Metroid * scene;
	Samus * samus;
	SpiderBug * spider;
	FlyingBat * bat;
	LPD3DXSPRITE spriteHandler;
public:
	World();
	World(LPD3DXSPRITE spriteHandler, Metroid * scene);
	~World();

	//void Init();
	void Update(float time);
	void Render();
	//void Destroy();
};