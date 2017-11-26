#include "Camera.h"

//Camera* Camera::_instance = NULL;

Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	_width = width;
	_height = height;
	_angle = angle;
	_scaleFactors = scaleFactors;

	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	int cameraX = _width / 2;
	int cameraY = _height / 2;
	if (_following)
	{
		cameraX = _following->getpos_x();
		cameraY = _following->getpos_y();
	}

	viewMatrix = D3DXMATRIX(
		_scaleFactors.x * cos(_angle), _scaleFactors.x * sin(_angle), 0, 0
		, -_scaleFactors.y * sin(_angle), _scaleFactors.y*cos(_angle), 0, 0, 0, 0,
		_scaleFactors.z, 0,
		-cameraX * _scaleFactors.x * cos(_angle) + cameraY * _scaleFactors.y *sin(_angle), -cameraX * _scaleFactors.y * sin(_angle) - cameraY* _scaleFactors.y*cos(_angle), 0, 1);
}

void Camera::Follow(Sprite* following)
{
	_following = following;
}

void Camera::Unfollow()
{
	_following = nullptr;
}

bool Camera::IsFollowing() const
{
	return _following != nullptr;
}

//void Camera::SetTransform(Game* gDevice) const
//{
//	gDevice->getdevice()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
//	gDevice->getdevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
//	gDevice->getdevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
//}
