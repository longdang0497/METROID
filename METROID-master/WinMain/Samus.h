#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include <dinput.h>

enum SamusStates {
	IDLE_LEFT,
	IDLE_RIGHT,
	LEFTING,
	RIGHTING,
	JUMPING_LEFT,
	JUMPING_RIGHT,
	IDLING_AIM_UP_LEFT,
	IDLING_AIM_UP_RIGHT,
	AIMING_UP_LEFT,
	AIMING_UP_RIGHT,
	TRANSFORM_LEFT,
	TRANSFORM_RIGHT,
};

class Samus : public GameObject
{
protected:
	LPD3DXSPRITE _SpriteHandler;		
	SamusStates state;
	
	Sprite *samus_appearing;
	Sprite *samus_right;
	Sprite *samus_left;
	Sprite *samus_jump_left;
	Sprite *samus_jump_right;
	Sprite *samus_idle_right;
	Sprite *samus_idle_left;
	Sprite *samus_aim_up_left;
	Sprite *samus_aim_up_right;
	Sprite *run_shooting_left;
	Sprite *run_shooting_right;
	Sprite *samus_idle_aim_up_left;
	Sprite *samus_idle_aim_up_right;
public:
	Samus();
	~Samus();
	
	void CreateSamus(LPDIRECT3DDEVICE9 d3ddv);

	virtual void setRECT(RECT value);
	RECT getRECTSamus();

	void SetX(float value);
	float GetX();
	void SetY(float value);
	float GetY();

	void SetVelocityX(float value);
	float GetVelocityX();
	void SetVelocityY(float value);
	float GetVelocityY();

	void SetVelocityXLast(float value);
	float GetVelocityXLast();
	
	SamusStates GetState();
	void SetState(SamusStates value);

	virtual void UpdateObject(int delta);
	void RenderSpriteSamus();
	void SpriteReset();
};
