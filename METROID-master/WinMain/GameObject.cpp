#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(int X, int Y, float Vx, float Vy)
{
	_x = X;
	_y = Y;
	_vx = Vx;
	_vy = Vy;
}

GameObject::~GameObject()
{
	ListChildren.clear();
}

ObjectType GameObject::GetType()
{
	return typeOBJECT;
}

void GameObject::SetBound(D3DXVECTOR2 value)
{
	rigidBody = value;
}

RECT GameObject::GetBound()
{
	objBound.left = _x - rigidBody.x / 2;
	objBound.right = _x + rigidBody.x / 2;
	objBound.top = _y + rigidBody.y / 2;
	objBound.bottom = _y - rigidBody.y / 2;

	return objBound;
}

RECT GameObject::GetRectCollision()
{
	RECT _temp;
	_temp.left = _x + mLeftDeviation;
	_temp.right = _x + obj->getwidth() - mRightDeviation;
	_temp.top = _y + obj->getheight() - mTopDeviation;
	_temp.bottom = _y + mBottonDeviation;
	return _temp;
}

RECT GameObject::getRECT()
{
	RECT _temp;
	_temp.left =_x;
	_temp.right = _x + obj->getwidth();
	_temp.top = _y + obj->getheight();
	_temp.bottom = _y;
	return _temp;
}

void GameObject::SetX(float value)
{
	_x = value;
}

float GameObject::GetX()
{
	return _x;
}

void GameObject::SetY(float value)
{
	_y = value;
}

float GameObject::GetY()
{
	return _y;
}

void GameObject::SetVx(float value)
{
	_vx = value;
}

float GameObject::GetVx()
{
	return _vx;
}

void GameObject::SetVy(float value)
{
	_vy = value;
}

float GameObject::GetVy()
{
	return _vy;
}

void GameObject::SetVelocityXLast(float value)
{
	_vx_last = value;
}

float GameObject::GetVelocityXLast()
{
	return _vx_last;
}

int GameObject::GetWidth()
{
	return obj->getwidth();
}

int GameObject::GetHeight()
{
	return obj->getheight();
}

void GameObject::Update()
{
}

void GameObject::UpdateObject(int delta)
{
}

void GameObject::Render()
{
}

void GameObject::UpdateCollison(GameObject* _samus, vector<GameObject*> _other, Game* _input, float frameTime)
{
}

float GameObject::getWCollision()
{
	return obj->getwidth() - mLeftDeviation - mRightDeviation;
}

float GameObject::getHCollision()
{
	return obj->getheight() - mTopDeviation - mBottonDeviation;
}

D3DXVECTOR2 GameObject::getPosCollision()
{
	D3DXVECTOR2 _temp;
	_temp.x = _x + mLeftDeviation;
	_temp.y = _y + mBottonDeviation;
	return _temp;
}

bool GameObject::Collision(RECT obj1, RECT obj2)
{
	return !(obj1.right < obj2.left	|| obj1.left > obj2.right || obj1.bottom > obj2.top	|| obj1.top < obj2.bottom);
}

RECT GameObject::getSweptBroadphaseBox(GameObject* _entity)
{
	RECT broadphasebox;
	if (_entity->GetVx() > 0)
	{
		broadphasebox.left = _entity->getPosCollision().x;
		broadphasebox.right = _entity->getPosCollision().x + _entity->GetVx() + _entity->getWCollision();
	}
	else
	{
		broadphasebox.left = _entity->getPosCollision().x + _entity->GetVx();
		broadphasebox.right = _entity->getPosCollision().x + _entity->getWCollision();
	}
	if (_entity->GetVy() > 0)
	{
		broadphasebox.bottom = _entity->getPosCollision().y;
		broadphasebox.top = _entity->getPosCollision().y + _entity->GetVy() + _entity->getHCollision();
	}
	else
	{
		broadphasebox.bottom = _entity->getPosCollision().y + _entity->GetVy();
		broadphasebox.top = _entity->getPosCollision().y + _entity->getHCollision();
	}
	return broadphasebox;
}

//calculate distance
bool GameObject::AABBCollision(GameObject* obj, DirectCollision& _normal, float& _time)
{
	if (!Collision(getSweptBroadphaseBox(this), getSweptBroadphaseBox(obj)))
	{
		_normal = LEFT;
		_time = 1.0f;
		return false;
	}
	// xInvEtry: khoảng cách từ box1.x + width đến box2.x <vào va chạm>
	// xInvExit: khoảnh cách từ box2.x + width đến box1.x <ra va chạm>

	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (GetVx() > 0.0f)
	{
		xInvEntry = obj->getPosCollision().x - (getPosCollision().x + getWCollision());
		xInvExit = (obj->getPosCollision().x + obj->getWCollision()) - getPosCollision().x;
	}
	else
	{
		// Tai sao khoang cach lai ra kq < 0
		xInvEntry = (obj->getPosCollision().x + obj->getWCollision()) - getPosCollision().x; // -
		xInvExit = obj->getPosCollision().x - (getPosCollision().x + getWCollision());	// -
	}

	if (GetVy() > 0.0f)
	{
		yInvEntry = obj->getPosCollision().y - (getPosCollision().y + getHCollision());
		yInvExit = (obj->getPosCollision().y + obj->getHCollision()) - getPosCollision().y;
	}
	else
	{
		yInvEntry = (obj->getPosCollision().y + obj->getHCollision()) - getPosCollision().y;	// -
		yInvExit = obj->getPosCollision().y - (getPosCollision().y + getHCollision());	// -
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	// THời gian va chạm và ra khỏi va chạm
	float xEntry, yEntry;
	float xExit, yExit;

	if (GetVx() == 0.0f)
	{
		// std::numeric_limits<float>::infinity() trả về số vô cùng
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / GetVx();
		xExit = xInvExit / GetVx();
	}

	if (GetVy() == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / GetVy();
		yExit = yInvExit / GetVy();
	}

	// find the earliest/latest times of collision
	// Thời gian nhanh nhất, và cuối cùng xảy ra va chạm, (xem va chạm trục nào trước, x hay y)
	float entryTime;
	float exitTime;

	entryTime = (xEntry > yEntry) ? xEntry : yEntry;

	exitTime = (xExit < yExit) ? xExit : yExit;

	// if there was no collision
	// Không xảy ra va chạm
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		_normal = LEFT;
		_time = 1.0f;
		return false;
	}
	else // Va chạm
	{
		// calculate normal of collided surface
		// Tính hướng trả về
		((xEntry < yEntry && xEntry > 0) || yEntry < 0) ?
			(_normal = (xInvEntry < 0.0f) ? RIGHT : LEFT) :
			(_normal = (yInvEntry <= 0.0f && GetVy() < 0.0f) ? TOP : BOTTOM);

		// return the time of collision
		// Thời gian xảy ra va chạm
		_time = entryTime;
		return true;
	}
}

//calculate collision time
bool GameObject::AABBCollision(GameObject* _a, GameObject* _b, DirectCollision& _normal, float& _time)
{
	if (!Collision(getSweptBroadphaseBox(_a), getSweptBroadphaseBox(_b)))
	{
		_normal = LEFT;
		_time = 1.0f;
		return false;
	}
	// xInvEtry: khoảng cách từ box1.x + width đến box2.x <vào va chạm>
	// xInvExit: khoảnh cách từ box2.x + width đến box1.x <ra va chạm>

	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (_a->GetVx() > 0.0f)
	{
		xInvEntry = _b->getPosCollision().x - (_a->getPosCollision().x + _a->getWCollision());
		xInvExit = (_b->getPosCollision().x + _b->getWCollision()) - _a->getPosCollision().x;
	}
	else
	{
		// Tai sao khoang cach lai ra kq < 0
		xInvEntry = (_b->getPosCollision().x + _b->getWCollision()) - _a->getPosCollision().x; // -
		xInvExit = _b->getPosCollision().x - (_a->getPosCollision().x + _a->getWCollision());	// -
	}

	if (_a->GetVy() > 0.0f)
	{
		yInvEntry = _b->getPosCollision().y - (_a->getPosCollision().y + _a->getHCollision());
		yInvExit = (_b->getPosCollision().y + _b->getHCollision()) - _a->getPosCollision().y;
	}
	else
	{
		yInvEntry = (_b->getPosCollision().y + _b->getHCollision()) - _a->getPosCollision().y;	// -
		yInvExit = _b->getPosCollision().y - (_a->getPosCollision().y + _a->getHCollision());	// -
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	// THời gian va chạm và ra khỏi va chạm
	float xEntry, yEntry;
	float xExit, yExit;

	if (_a->GetVx() == 0.0f)
	{
		// std::numeric_limits<float>::infinity() trả về số vô cùng
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / _a->GetVx();
		xExit = xInvExit / _a->GetVx();
	}

	if (_a->GetVy() == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / _a->GetVy();
		yExit = yInvExit / _a->GetVy();
	}

	// find the earliest/latest times of collision
	// Thời gian nhanh nhất, và cuối cùng xảy ra va chạm, (xem va chạm trục nào trước, x hay y)
	float entryTime;
	float exitTime;
	if (xEntry > yEntry)
	{
		entryTime = xEntry;
	}
	else
	{
		entryTime = yEntry;
	}

	if (xExit < yExit)
	{
		exitTime = xExit;
	}
	else
	{
		exitTime = yExit;
	}
	// if there was no collision
	// Không xảy ra va chạm
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		_normal = LEFT;
		_time = 1.0f;
		return false;
	}
	else // Va chạm
	{
		// calculate normal of collided surface
		// Tính hướng trả về
		if ((xEntry < yEntry && xEntry > 0) || yEntry < 0)
		{
			if (xInvEntry < 0.0f)
			{
				_normal = RIGHT;
			}
			else
			{
				_normal = LEFT;
			}
		}
		else
		{
			if (yInvEntry <= 0.0f && _a->GetVy() < 0.0f)
			{
				_normal = TOP;
			}
			else
			{
				_normal = BOTTOM;
			}
		}

		// return the time of collision
		// Thời gian xảy ra va chạm
		_time = entryTime;
		return true;
	}
}
