#include "Collider.h"

Collider::Collider()
{
}

Collider::~Collider()
{
}

float Collider::GetTop()
{
	return top;
}

void Collider::SetTop(float _top)
{
	top = _top;
}

float Collider::GetLeft()
{
	return left;
}

void Collider::SetLeft(float _left)
{
	left = _left;
}

float Collider::GetBottom()
{
	return bottom;
}

void Collider::SetBottom(float _bot)
{
	bottom = _bot;
}

float Collider::GetRight()
{
	return right;
}

void Collider::SetRight(float _right)
{
	right = _right;
}

void Collider::setCollider(float top, float left, float bottom, float right)
{
	this->top = top;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
}
