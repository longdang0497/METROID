#include "GroupObject.h"

GroupObject::GroupObject()
{
}

GroupObject::GroupObject(World * manager)
{
	this->manager = manager;
}

GroupObject::~GroupObject()
{
}

std::vector<GameObject*> GroupObject::GetListGO()
{
	return objects;
}

int GroupObject::GetSize()
{
	return size;
}

void GroupObject::AddGameObject(GameObject * target)
{
	// trước khi thêm kiểm tra trùng lặp
	for (int i = 0; i < size; i++)
	{
		// Nếu trùng thì dừng
		if (objects[i] == target)
			return;
	}

	objects.push_back(target);
	size++;
}

void GroupObject::Update(int t)
{
	for (int i = 0; i < size; i++)
	{
		objects[i]->UpdateObject(t);
	}
}

void GroupObject::UpdateActive(int t)
{
	for (int i = 0; i < size; i++)
	{
		if (objects[i]->CheckActive())
		{
			objects[i]->UpdateObject(t);
		}
	}
}

void GroupObject::Render()
{
	for (int i = 0; i < size; i++)
	{
		objects[i]->Render();
	}
}

void GroupObject::GetGroupObjectFrom(GroupObject * group)
{
	int group_size = group->size;
	for (int i = 0; i < group_size; i++)
	{
		if (group->objects[i]->CheckActive())
		{
			this->AddGameObject(group->objects[i]);
		}
	}
}
