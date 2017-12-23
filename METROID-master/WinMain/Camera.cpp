#include "Camera.h"

int Camera::_curCamX = 0;
int Camera::_curCamY = 0;

int Camera::maxX = 2000;
int Camera::minX = 0;

int Camera::maxY = 0;
int Camera::minY = 0;

int Camera::_width = 640;
int Camera::_height = 480;

Camera::Camera()
{
	SetDemension(GAME_SCREEN_RESOLUTION_640_480_24);
}

Camera::~Camera()
{

}

void Camera::SetCameraX(int pos_x)
{
	_curCamX = pos_x - 320;
	if (_curCamX < minX)
	{
		_curCamX = minX;
	}
	if (_curCamX >= maxX)
	{
		_curCamX = maxX;
	}
}

void Camera::SetDemension(int mode)
{
	switch (mode)
	{
	case GAME_SCREEN_RESOLUTION_640_480_24:
		_width = 640;
		_height = 480;
		break;
	case GAME_SCREEN_RESOLUTION_800_600_24:
		_width = 800;
		_height = 600;
		break;
	case GAME_SCREEN_RESOLUTION_1024_768_24:
		_width = 1024;
		_height = 768;
		break;
	}
}

//void Camera::SetCameraY()
//{
//	int result = 600;
//	return result;
//}
