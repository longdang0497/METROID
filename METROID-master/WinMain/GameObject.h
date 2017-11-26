#pragma once
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include <limits>
#include <algorithm>
#include "Define.h"
#include <vector>

class Game;

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
	Sprite *obj;
	vector<GameObject*> ListChildren; //spider, bullet, bat, ...

	int _x;
	int _y;

	float _vx;
	float _vy;

	float _vx_last;

	float mLeftDeviation;
	float mRightDeviation;
	float mTopDeviation;
	float mBottonDeviation;

	bool isAlive;
	DWORD last_time;
public:
	GameObject();
	GameObject(int X, int Y, float Vx, float Vy);
	~GameObject();

	ObjectType GetType();

	void SetBound(D3DXVECTOR2 value);
	RECT GetBound();
	RECT GetRectCollision();
	RECT getRECT();

	void SetX(float value);
	float GetX();
	void SetY(float value);
	float GetY();

	void SetVx(float value);
	float GetVx();
	void SetVy(float value);
	float GetVy();

	void SetVelocityXLast(float value);
	float GetVelocityXLast();

	int GetWidth();
	int GetHeight();

	void setListChildren(vector<GameObject*> _list) { ListChildren = _list; }
	vector<GameObject*> getListChildren() { return ListChildren; }

	virtual void Update();
	virtual void UpdateObject(int delta);
	virtual void Render();
	virtual void UpdateCollison(GameObject * _samus, vector<GameObject*> _other, Game * _input, float frameTime);

	float getWCollision();
	float getHCollision();
	D3DXVECTOR2 getPosCollision();
	bool Collision(RECT obj1, RECT obj2);	//AABB
	RECT getSweptBroadphaseBox(GameObject * _entity);
	bool AABBCollision(GameObject * obj, DirectCollision & _normal, float & _time);  //calculate distance
	bool AABBCollision(GameObject * _a, GameObject * _b, DirectCollision & _normal, float & _time);	//calculate collision time
};
