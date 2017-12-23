#pragma once
#include "Define.h"

class Camera
{
public:
	static int maxX;
	static int minX;

	static int maxY;
	static int minY;

	static int _curCamX;
	static int _curCamY;

	static int _width;	// width của viewport
	static int _height;	// height của viewport
public:
	Camera();	//Default Constructor
	~Camera();	//Default destructor

	static void SetCameraX(int pos_x);
	/*static void SetCameraY(int pos_y);*/

	static void SetDemension(int mode);
};

