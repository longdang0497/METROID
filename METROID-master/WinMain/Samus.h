#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include <vector>

class Game;

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
	TRANSFORM_BALL_LEFT,
	TRANSFORM_BALL_RIGHT,
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
	Sprite *samus_morph_left;
	Sprite *samus_morph_right;
public:
	Samus();
	~Samus();
	
	void CreateSamus(LPDIRECT3DDEVICE9 d3ddv);
	
	SamusStates GetState();
	void SetState(SamusStates value);

	void UpdateCollison(GameObject* _samus, vector<GameObject*> _list, Game * _input, float);
	virtual void UpdateObject(int delta);
	virtual void Update();
	void RenderSpriteSamus();
	void SpriteReset();
};
