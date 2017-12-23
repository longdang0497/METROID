#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	delete(object);
	delete(collider);
	delete(broadPhaseBox);
}

bool GameObject::CheckActive()
{
	return isActive;
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
	/*_temp.left = _x + mLeftDeviation;
	_temp.right = _x + object->getwidth() - mRightDeviation;
	_temp.top = _y + obj->getheight() - mTopDeviation;
	_temp.bottom = _y + mBottonDeviation;*/
	return _temp;
}

RECT GameObject::getRECT()
{
	RECT _temp;
	/*_temp.left =_x;
	_temp.right = _x + obj->getwidth();
	_temp.top = _y + obj->getheight();
	_temp.bottom = _y;*/
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

float GameObject::GetlastPosX()
{
	return _x_last;
}

void GameObject::SetlastPosX(float posx)
{
	_x_last = posx;
}

float GameObject::GetlastPosY()
{
	return _y_last;
}

void GameObject::SetlastPosY(float posy)
{
	_y_last = posy;
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

void GameObject::SetVelocityYLast(float value)
{
	_vy_last = value;
}

float GameObject::GetVelocityYLast()
{
	return _vy_last;
}

int GameObject::GetWidth()
{
	return _width;
}

void GameObject::SetWidth(int value)
{
	_width = value;
}

int GameObject::GetHeight()
{
	return _height;
}

void GameObject::SetHeight(int value)
{
	_height = value;
}

Collider * GameObject::GetCollider()
{
	return collider;
}

void GameObject::UpdateObject(float delta)
{
}

void GameObject::Render()
{
}

void GameObject::Reset(int x, int y)
{
	isActive = true;
	this->_x = x;
	this->_y = y;
}

void GameObject::UnActiveObject()
{
}

bool GameObject::IsCollide(GameObject * target)
{
	//both object must have collider in order for collision
	if ((target->GetCollider() == NULL) || (this->collider == NULL))
		return false;

	// cạnh trái của this > cạnh phải của target
	if ((_x + collider->GetLeft()) > (target->GetX() + target->GetCollider()->GetRight()))
		return false;

	// cạnh phải của this < cạnh trái của target
	if ((_x + collider->GetRight()) < (target->GetX() + target->GetCollider()->GetLeft()))
		return false;

	// cạnh trên của this < cạnh dưới của target
	if ((_y + collider->GetTop()) < (target->GetY() + target->GetCollider()->GetBottom()))
		return false;

	// cạnh dưới của this > cạnh trên của target
	if ((_y + collider->GetBottom()) > (target->GetX() + target->GetCollider()->GetTop()))
		return false;

	// ko thoả điều kiện nào hết => đang nằm lồng vào nhau
	return true;
}

bool GameObject::IsInside(GameObject * target)
{
	// cả 2 phải có collider mới va chạm được
	if ((target->GetCollider() == NULL) || (this->collider == NULL))
		return false;

	if (((_x + collider->GetLeft()) > (target->GetX() + target->GetCollider()->GetLeft())) &&
		((_x + collider->GetRight()) < (target->GetX() + target->GetCollider()->GetRight())) &&
		((_x + collider->GetTop()) < (target->GetX() + target->GetCollider()->GetTop())) &&
		((_x + collider->GetBottom()) > (target->GetX() + target->GetCollider()->GetBottom())))
		return true;

	// else
	return false;
}

// tính thời gian va chạm
float GameObject::SweptAABB(GameObject * target, const float & DeltaTime)
{
	if ((target->GetCollider() == NULL) || (this->collider == NULL))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	// ---------------======== Broad - Phasing ============-------------

	// delta velocity
	float deltaVX = ((this->_vx) - (target->_vx)) * DeltaTime;
	float deltaVY = ((this->_vy) - (target->_vy)) * DeltaTime;

	// tạo ra cái hộp bao quanh quỹ đạo của "this"
	if (broadPhaseBox == NULL)
	{
		broadPhaseBox = new Collider();
	}
	if (deltaVX > 0.0f)	// left & right
	{
		broadPhaseBox->SetLeft(this->collider->GetLeft());
		broadPhaseBox->SetRight(this->collider->GetRight() + deltaVX);
	}
	else
	{
		broadPhaseBox->SetLeft(this->collider->GetLeft() + deltaVX);
		broadPhaseBox->SetRight(this->collider->GetRight());
	}

	if (deltaVY > 0.0f) // top & bottom
	{
		broadPhaseBox->SetTop((this->collider->GetTop() + deltaVY));
		broadPhaseBox->SetBottom(this->collider->GetBottom());
	}
	else
	{
		broadPhaseBox->SetTop(this->collider->GetTop());
		broadPhaseBox->SetBottom((this->collider->GetBottom() + deltaVY));
	}

	// --- xét coi Box có lồng vào target hay không ------------------

	// cạnh trái của hộp > cạnh phải của target
	if ((_x + broadPhaseBox->GetLeft()) > (target->GetX() + target->GetCollider()->GetRight()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh phải của hộp < cạnh trái của target
	if ((_x + broadPhaseBox->GetRight()) < (target->GetX() + target->GetCollider()->GetLeft()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh trên của hộp < cạnh dưới của target
	if ((_y + broadPhaseBox->GetTop()) < (target->GetY() + target->GetCollider()->GetBottom()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh dưới của hộp > cạnh trên của target
	if ((_y + broadPhaseBox->GetBottom()) > (target->GetY() + target->GetCollider()->GetTop()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// end of Broad - Phasing
	// --------------------------===============================----------------------------


	// ---=== xét xem có lồng nhau ngay từ đầu không ===---
	if (this->IsCollide(target))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 0.0f;
	}

	float dxEntry, dyEntry;
	float dxExit, dyExit;

	if (deltaVX > 0.0f)
	{
		dxEntry = (target->GetX() + target->GetCollider()->GetLeft()) - (this->_x + this->collider->GetRight());
		dxExit = (target->GetX() + target->GetCollider()->GetRight()) - (this->_x + this->collider->GetLeft());
	}
	else
	{
		dxEntry = (target->GetX() + target->GetCollider()->GetRight()) - (this->_x + this->collider->GetLeft());
		dxExit = (target->GetX() + target->GetCollider()->GetLeft()) - (this->_x + this->collider->GetRight());
	}

	if (deltaVY > 0.0f)
	{
		dyEntry = (target->GetY() + target->collider->GetBottom()) - (this->_y + this->collider->GetTop());
		dyExit = (target->GetY() + target->collider->GetTop()) - (this->_y + this->collider->GetBottom());
	}
	else
	{
		dyEntry = (target->GetY() + target->collider->GetTop()) - (this->_y + this->collider->GetBottom());
		dyExit = (target->GetY() + target->collider->GetBottom()) - (this->_y + this->collider->GetTop());
	}

	// thời gian va chạm của mỗi chiều
	float txEntry, tyEntry;
	float txExit, tyExit;

	if (deltaVX == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / deltaVX;
		txExit = dxExit / deltaVX;
	}

	if (deltaVY == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / deltaVY;
		tyExit = dyExit / deltaVY;
	}

	// --- thời gian va chạn theo 2 chiều
	float entryTimeScale = max(txEntry, tyEntry);
	float exitTimeScale = min(txExit, tyExit);

	// nếu như không có va chạm
	if ((entryTimeScale > exitTimeScale) || ((txEntry < 0.0f) && (tyEntry < 0.0f))
		|| (txEntry > 1.0f) || (tyEntry > 1.0f))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}


	// tính toán vector pháp tuyến của bề mặt va chạm
	if (txEntry > tyEntry)
	{
		if (dxEntry < 0.0f)
		{
			normalx = 1.0f;
			normaly = 0.0f;
		}
		else
		{
			normalx = -1.0f;
			normaly = 0.0f;
		}
	}
	else
	{
		if (dyEntry < 0.0f)
		{
			normalx = 0.0f;
			normaly = 1.0f;
		}
		else
		{
			normalx = 0.0f;
			normaly = -1.0f;
		}
	}

	//	0.0f < scale < 1.0f là có va chạm
	// 0.0f va chạm lồng vào nhau
	return entryTimeScale;
}

// di chuyển sát tường (xử lý va chạm)
void GameObject::Response(GameObject * target, const float & DeltaTime, const float & CollisionTimeScale)
{
	_x += _vx * (CollisionTimeScale * DeltaTime);
	_y += _vy * (CollisionTimeScale * DeltaTime);
}

// bật ngược ra khi va chạm (Xử lý va chạm)
void GameObject::Deflect(GameObject * target, const float & DeltaTime, const float & CollisionTimeScale)
{
	// di chuyển vào sát tường trước
	this->Response(target, DeltaTime, CollisionTimeScale);

	// rồi mới bật ra
	if (normalx > 0.1f)	// tông bên phải
	{
		if (_vx < -0.0f)// đang chạy qua trái => văng ngược lại
			_vx *= -1;
	}
	else if (normalx < -0.1f) // tông bên trái
	{
		if (_vx > 0.0f)//	đang chạy qua phải => văng ngược lại
			_vx *= -1;
	}

	if (normaly > 0.1f) // tông phía trên
	{
		if (_vy < -0.0f)// đang rơi xuống => văng lên trên
			_vy *= -1;
	}
	else if (normaly < -0.1f) // tông phía dưới
	{
		if (_vy > 0.0f)// đang bay lên => văng xuống
			_vy *= -1;
	}

	_x += _vx * (1.0f - CollisionTimeScale) * DeltaTime;
	_y += _vy * (1.0f - CollisionTimeScale) * DeltaTime;
}

// nâng lên khi va chạm với ground
void GameObject::SlideFromGround(GameObject * target, const float & DeltaTime, const float & CollisionTimeScale)
{
	//ResponseFrom(target, _DeltaTime, collisionTimeScale);
	// lỡ đụng 2,3 ground mà chạy cái này nhiều lần sẽ rất sai
	// "góc lag" sẽ làm đi luôn vào trong tường


	if (normalx > 0.1f)	// tông bên phải
	{
		this->_x = (target->GetX() + target->collider->GetRight() - this->collider->GetLeft()) + 0.1f;
		_x -= _vx * DeltaTime;
		//vx = 0.0f;
	}

	else if (normalx < -0.1f)// tông bên trái
	{
		this->_x = (target->GetX() + target->collider->GetLeft() - this->collider->GetRight()) - 0.1f;
		_x -= _vx * DeltaTime;
		//vx = 0.0f;
	}

	else if (normaly > 0.1f)	// tông ở trên
	{
		this->_y = (target->_y + target->collider->GetTop() - this->collider->GetBottom()) + 0.1f;
		_vy = 0.0f;
	}
	else
		return;
}

//float GameObject::getWCollision()
//{
//	return obj->getwidth() - mLeftDeviation - mRightDeviation;
//}
//
//float GameObject::getHCollision()
//{
//	return obj->getheight() - mTopDeviation - mBottonDeviation;
//}
//
//D3DXVECTOR2 GameObject::getPosCollision()
//{
//	D3DXVECTOR2 _temp;
//	_temp.x = _x + mLeftDeviation;
//	_temp.y = _y + mBottonDeviation;
//	return _temp;
//}
//
//bool GameObject::Collision(RECT obj1, RECT obj2)
//{
//	return !(obj1.right < obj2.left	|| obj1.left > obj2.right || obj1.bottom > obj2.top	|| obj1.top < obj2.bottom);
//}
//
//RECT GameObject::getSweptBroadphaseBox(GameObject* _entity)
//{
//	RECT broadphasebox;
//	if (_entity->GetVx() > 0)
//	{
//		broadphasebox.left = _entity->getPosCollision().x;
//		broadphasebox.right = _entity->getPosCollision().x + _entity->GetVx() + _entity->getWCollision();
//	}
//	else
//	{
//		broadphasebox.left = _entity->getPosCollision().x + _entity->GetVx();
//		broadphasebox.right = _entity->getPosCollision().x + _entity->getWCollision();
//	}
//	if (_entity->GetVy() > 0)
//	{
//		broadphasebox.bottom = _entity->getPosCollision().y;
//		broadphasebox.top = _entity->getPosCollision().y + _entity->GetVy() + _entity->getHCollision();
//	}
//	else
//	{
//		broadphasebox.bottom = _entity->getPosCollision().y + _entity->GetVy();
//		broadphasebox.top = _entity->getPosCollision().y + _entity->getHCollision();
//	}
//	return broadphasebox;
//}
//
////calculate distance
//bool GameObject::AABBCollision(GameObject* obj, DirectCollision& _normal, float& _time)
//{
//	if (!Collision(getSweptBroadphaseBox(this), getSweptBroadphaseBox(obj)))
//	{
//		_normal = LEFT;
//		_time = 1.0f;
//		return false;
//	}
//	// xInvEtry: khoảng cách từ box1.x + width đến box2.x <vào va chạm>
//	// xInvExit: khoảnh cách từ box2.x + width đến box1.x <ra va chạm>
//
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInvExit;
//
//	// find the distance between the objects on the near and far sides for both x and y
//	if (GetVx() > 0.0f)
//	{
//		xInvEntry = obj->getPosCollision().x - (getPosCollision().x + getWCollision());
//		xInvExit = (obj->getPosCollision().x + obj->getWCollision()) - getPosCollision().x;
//	}
//	else
//	{
//		// Tai sao khoang cach lai ra kq < 0
//		xInvEntry = (obj->getPosCollision().x + obj->getWCollision()) - getPosCollision().x; // -
//		xInvExit = obj->getPosCollision().x - (getPosCollision().x + getWCollision());	// -
//	}
//
//	if (GetVy() > 0.0f)
//	{
//		yInvEntry = obj->getPosCollision().y - (getPosCollision().y + getHCollision());
//		yInvExit = (obj->getPosCollision().y + obj->getHCollision()) - getPosCollision().y;
//	}
//	else
//	{
//		yInvEntry = (obj->getPosCollision().y + obj->getHCollision()) - getPosCollision().y;	// -
//		yInvExit = obj->getPosCollision().y - (getPosCollision().y + getHCollision());	// -
//	}
//
//	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
//	// THời gian va chạm và ra khỏi va chạm
//	float xEntry, yEntry;
//	float xExit, yExit;
//
//	if (GetVx() == 0.0f)
//	{
//		// std::numeric_limits<float>::infinity() trả về số vô cùng
//		xEntry = -std::numeric_limits<float>::infinity();
//		xExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		xEntry = xInvEntry / GetVx();
//		xExit = xInvExit / GetVx();
//	}
//
//	if (GetVy() == 0.0f)
//	{
//		yEntry = -std::numeric_limits<float>::infinity();
//		yExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		yEntry = yInvEntry / GetVy();
//		yExit = yInvExit / GetVy();
//	}
//
//	// find the earliest/latest times of collision
//	// Thời gian nhanh nhất, và cuối cùng xảy ra va chạm, (xem va chạm trục nào trước, x hay y)
//	float entryTime;
//	float exitTime;
//
//	entryTime = (xEntry > yEntry) ? xEntry : yEntry;
//
//	exitTime = (xExit < yExit) ? xExit : yExit;
//
//	// if there was no collision
//	// Không xảy ra va chạm
//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
//	{
//		_normal = LEFT;
//		_time = 1.0f;
//		return false;
//	}
//	else // Va chạm
//	{
//		// calculate normal of collided surface
//		// Tính hướng trả về
//		((xEntry < yEntry && xEntry > 0) || yEntry < 0) ?
//			(_normal = (xInvEntry < 0.0f) ? RIGHT : LEFT) :
//			(_normal = (yInvEntry <= 0.0f && GetVy() < 0.0f) ? TOP : BOTTOM);
//
//		// return the time of collision
//		// Thời gian xảy ra va chạm
//		_time = entryTime;
//		return true;
//	}
//}
//
////calculate collision time
//bool GameObject::AABBCollision(GameObject* _a, GameObject* _b, DirectCollision& _normal, float& _time)
//{
//	if (!Collision(getSweptBroadphaseBox(_a), getSweptBroadphaseBox(_b)))
//	{
//		_normal = LEFT;
//		_time = 1.0f;
//		return false;
//	}
//	// xInvEtry: khoảng cách từ box1.x + width đến box2.x <vào va chạm>
//	// xInvExit: khoảnh cách từ box2.x + width đến box1.x <ra va chạm>
//
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInvExit;
//
//	// find the distance between the objects on the near and far sides for both x and y
//	if (_a->GetVx() > 0.0f)
//	{
//		xInvEntry = _b->getPosCollision().x - (_a->getPosCollision().x + _a->getWCollision());
//		xInvExit = (_b->getPosCollision().x + _b->getWCollision()) - _a->getPosCollision().x;
//	}
//	else
//	{
//		// Tai sao khoang cach lai ra kq < 0
//		xInvEntry = (_b->getPosCollision().x + _b->getWCollision()) - _a->getPosCollision().x; // -
//		xInvExit = _b->getPosCollision().x - (_a->getPosCollision().x + _a->getWCollision());	// -
//	}
//
//	if (_a->GetVy() > 0.0f)
//	{
//		yInvEntry = _b->getPosCollision().y - (_a->getPosCollision().y + _a->getHCollision());
//		yInvExit = (_b->getPosCollision().y + _b->getHCollision()) - _a->getPosCollision().y;
//	}
//	else
//	{
//		yInvEntry = (_b->getPosCollision().y + _b->getHCollision()) - _a->getPosCollision().y;	// -
//		yInvExit = _b->getPosCollision().y - (_a->getPosCollision().y + _a->getHCollision());	// -
//	}
//
//	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
//	// THời gian va chạm và ra khỏi va chạm
//	float xEntry, yEntry;
//	float xExit, yExit;
//
//	if (_a->GetVx() == 0.0f)
//	{
//		// std::numeric_limits<float>::infinity() trả về số vô cùng
//		xEntry = -std::numeric_limits<float>::infinity();
//		xExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		xEntry = xInvEntry / _a->GetVx();
//		xExit = xInvExit / _a->GetVx();
//	}
//
//	if (_a->GetVy() == 0.0f)
//	{
//		yEntry = -std::numeric_limits<float>::infinity();
//		yExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		yEntry = yInvEntry / _a->GetVy();
//		yExit = yInvExit / _a->GetVy();
//	}
//
//	// find the earliest/latest times of collision
//	// Thời gian nhanh nhất, và cuối cùng xảy ra va chạm, (xem va chạm trục nào trước, x hay y)
//	float entryTime;
//	float exitTime;
//	if (xEntry > yEntry)
//	{
//		entryTime = xEntry;
//	}
//	else
//	{
//		entryTime = yEntry;
//	}
//
//	if (xExit < yExit)
//	{
//		exitTime = xExit;
//	}
//	else
//	{
//		exitTime = yExit;
//	}
//	// if there was no collision
//	// Không xảy ra va chạm
//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
//	{
//		_normal = LEFT;
//		_time = 1.0f;
//		return false;
//	}
//	else // Va chạm
//	{
//		// calculate normal of collided surface
//		// Tính hướng trả về
//		if ((xEntry < yEntry && xEntry > 0) || yEntry < 0)
//		{
//			if (xInvEntry < 0.0f)
//			{
//				_normal = RIGHT;
//			}
//			else
//			{
//				_normal = LEFT;
//			}
//		}
//		else
//		{
//			if (yInvEntry <= 0.0f && _a->GetVy() < 0.0f)
//			{
//				_normal = TOP;
//			}
//			else
//			{
//				_normal = BOTTOM;
//			}
//		}
//
//		// return the time of collision
//		// Thời gian xảy ra va chạm
//		_time = entryTime;
//		return true;
//	}
//}
