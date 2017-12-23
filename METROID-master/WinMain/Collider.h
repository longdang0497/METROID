#pragma once
#include <d3dx9.h>
class GameObject;

class Collider
{
private:
	float top;
	float bottom;
	float left;
	float right;
	GameObject * owner;
public:
	Collider();
	~Collider();

	float GetTop();
	void SetTop(float _top);
	float GetLeft();
	void SetLeft(float _left);
	float GetBottom();
	void SetBottom(float _bot);
	float GetRight();
	void SetRight(float _right);
	
	void setCollider(float,float,float,float);
};
