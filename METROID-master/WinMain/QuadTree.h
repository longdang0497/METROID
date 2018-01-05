#pragma once
#include <map>
#include "QNode.h"
#include "Define.h"

class QuadTree
{
public:
	map<int, QNode*> mapQuadtree;

	QuadTree();
	~QuadTree();

	void LoadNodeFromFile(LPWSTR file_path);
	//void CreateQuadTree();
};
