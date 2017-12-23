#pragma once
#include "GameObject.h"
#include <vector>

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
	RUN_SHOOT_LEFT,
	RUN_SHOOT_RIGHT,
	TRANSFORM_BALL_LEFT,
	TRANSFORM_BALL_RIGHT,
	SAMUS_SOMERSAULT_LEFT,
	SAMUS_SOMERSAULT_RIGHT,
	JUMPING_SHOOTING_LEFT,
	JUMPING_SHOOTING_RIGHT,
	JUMPING_AIM_UP_LEFT,
	JUMPING_AIM_UP_RIGHT
};

class Samus : public GameObject
{
protected:
	SamusStates state;
	#pragma region Sprite Samus
	Sprite * samus_appearing;
	Sprite * samus_right;
	Sprite * samus_left;
	Sprite * samus_jump_left;
	Sprite * samus_jump_right;
	Sprite * samus_idle_right;
	Sprite * samus_idle_left;
	Sprite * samus_aim_up_left;
	Sprite * samus_aim_up_right;
	Sprite * run_shooting_left;
	Sprite * run_shooting_right;
	Sprite * samus_idle_aim_up_left;
	Sprite * samus_idle_aim_up_right;
	Sprite * samus_morph_left;
	Sprite * samus_morph_right;
	Sprite * samus_somersault_left;
	Sprite * samus_somersault_right;
	Sprite * samus_jumping_shooting_left;
	Sprite * samus_jumping_shooting_right;
	Sprite * samus_jump_aim_up_left;
	Sprite * samus_jump_aim_up_right;
#pragma endregion
public:
	Samus();
	Samus(LPD3DXSPRITE spriteHandler, World * manager);
	~Samus();
	
	void CreateSamus(LPDIRECT3DDEVICE9 d3ddv);
	
	SamusStates GetState();
	void SetState(SamusStates value);

	void Reset(int x, int y);
	void UpdateObject(float delta);
	void UnActiveObject();
	void Render();
	void SpriteReset();
};
