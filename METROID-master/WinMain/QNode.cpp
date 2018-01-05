#include "QNode.h"

QNode::QNode()
{
	nodeID = 0;
	x = 0;
	y = 0;
	width = 0;
	height = 0;

	//Gán bằng NULL cho chắc
	top_left = NULL;
	top_right = NULL;
	bot_left = NULL;
	bot_right = NULL;

	//Khởi tạo GroupbObject rỗng 
	objects = new GroupObject(nullptr);
}

QNode::QNode(int id, int x, int y, int width, int height)
{
	this->nodeID = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	//Gán bằng NULL cho chắc
	top_left = NULL;
	top_right = NULL;
	bot_left = NULL;
	bot_right = NULL;

	//Khởi tạo GroupbObject rỗng 
	objects = new GroupObject(nullptr);
}

QNode::~QNode()
{
}

bool QNode::IsIntersectViewPort()
{
	// Kiểm tra phía trên viewport
	if ((y + height) > Camera::_curCamY)
		return false;

	// Kiểm tra bên phải viewport
	if (x > Camera::_curCamX + Camera::_width)
		return false;

	// Kiểm tra phía dưới viewport
	if (y < Camera::_curCamY + Camera::_height)
		return false;

	// Kiểm tra phía bên trái viewport
	if (x + width < Camera::_curCamX)
		return  false;

	return true;
}

int QNode::GetParentID()
{
	// Do tool MapEditor tính theo hệ 8
	return nodeID / NODE_FACTOR;
}

int QNode::GetOffsetID()
{
	return nodeID % NODE_FACTOR;
}

void QNode::SendObjectsToGroup(GroupObject * target)
{
	// Nếu node này không giao với viewport thì dừng
	if (!this->IsIntersectViewPort())
		return;

	// Nếu node này không phải là node lá thì xét tiếp
	if (this->top_left != NULL)
	{
		this->top_left->SendObjectsToGroup(target);
		this->top_right->SendObjectsToGroup(target);
		this->bot_right->SendObjectsToGroup(target);
		this->bot_left->SendObjectsToGroup(target);
	}
	else // Nếu là node lá thì target sẽ lấy object về
	{
		target->GetGroupObjectFrom(this->objects);
	}
}

/*void QNode::deleteObjects()
{
	// Xóa các object đã bị DESTROY ra khỏi list object hiện tại
	if (objects->GetSize() != 0)
	{
		int i = 0;
		while (i < objects->GetSize())
		{
			// Nếu object có trạng thái DESTROY thì xóa khỏi list
			if (_objects[i]->getStatus() == eStatus::DESTROY)
			{
				auto object = _objects[i];
				_objects.erase(_objects.begin() + i);
				object->release();
				delete object;
			}
			else
				i++;
		}
	}

	// Gọi đệ quy xóa các object đã bị DESTROY ra khỏi các Node con
	if (!_children.empty())
		for (auto child : _children)
			child->deleteObjects();
}*/
