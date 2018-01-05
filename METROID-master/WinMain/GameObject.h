#pragma once
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include <limits>
#include <algorithm>
#include "Define.h"
#include <vector>
#include "World.h"
#include "Collider.h"

enum DirectCollision
{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM
};

class GameObject
{
protected:
	RECT objBound;
	D3DXVECTOR2 rigidBody;
	World * manager;	//pointer to World to use when needed
	Sprite * object;
	LPD3DXSPRITE spriteHandler;

	Collider * collider;
	Collider * broadPhaseBox;

	float _x;
	float _y;
	float _x_last;
	float _y_last;

	int _width;
	int _height;

	float _vx;
	float _vy;

	float _vx_last;
	float _vy_last;

	float mLeftDeviation;
	float mRightDeviation;
	float mTopDeviation;
	float mBottonDeviation;

	float collisionTimeScale; // thời gian va chạm
	float normalx;	// "vector pháp tuyến" để xét va chạm
	float normaly;

	bool isActive;	//the game object is active or not
	DWORD last_time;	//control the animation rate
	ObjectType type;
public:
	GameObject();
	~GameObject();

	#pragma region Get - Set Method
	bool CheckActive();

	ObjectType getType();
	void setType(ObjectType _type);

	void SetBound(D3DXVECTOR2 value);
	RECT GetBound();
	RECT GetRectCollision();
	RECT getRECT();

	void SetX(float value);
	float GetX();
	void SetY(float value);
	float GetY();

	float GetlastPosX();
	void SetlastPosX(float posx);
	float GetlastPosY();
	void SetlastPosY(float posy);

	void SetVx(float value);
	float GetVx();
	void SetVy(float value);
	float GetVy();

	void SetVelocityXLast(float value);
	float GetVelocityXLast();
	void SetVelocityYLast(float value);
	float GetVelocityYLast();

	int GetWidth();
	void SetWidth(int value);
	int GetHeight();
	void SetHeight(int value);

	Collider * GetCollider();
#pragma endregion

	virtual void UpdateObject(float delta);
	virtual void Render();
	virtual void Reset(int x, int y);		
	virtual void UnActiveObject();
#pragma region Collision
	bool IsCollide(GameObject* target);	//check if collide
	bool IsInside(GameObject* target);	//check if object go throuugh or stay inside the other object
	//bool IsInCamera();

	float SweptAABB(GameObject *target, const float &DeltaTime);

	// xử lý khi có va chạm
	void Response(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	void Deflect(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	//void Push(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	//void Slide(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	void SlideFromGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
#pragma endregion
	//float getWCollision();
	//float getHCollision();
	//D3DXVECTOR2 getPosCollision();
	//bool Collision(RECT obj1, RECT obj2);	//AABB
	//RECT getSweptBroadphaseBox(GameObject * _entity);
	//bool AABBCollision(GameObject * obj, DirectCollision & _normal, float & _time);  //calculate distance
	//bool AABBCollision(GameObject * _a, GameObject * _b, DirectCollision & _normal, float & _time);	//calculate collision time
};
