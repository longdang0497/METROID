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

//Camera::Camera(GameObject * follow)
//{
//	_follow = follow;
//	_width = 800 /*Graphics::GetInstance()->GetScreenWidth()*/;
//	_height = 600 /*Graphics::GetInstance()->GetScreenHeight()*/;
//
//	/*_position = D3DXVECTOR2((_width*1.0) / 2, (_height*1.0) / 2);
//	_position.x = _follow->GetPosition().x;*/
//
//	this->_instance = this;
//}

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

//Camera * Camera::GetInstance()
//{
//	if (!_instance)
//		_instance = new Camera();
//
//	return _instance;
//}
//
//void Camera::UpdateCam(float deltaTime)
//{
//	GameObject::UpdateObject(deltaTime);
//
//	/*if (_follow != NULL && (_input->IsKeyPressed(DIK_LEFT) || _input->IsKeyPressed(DIK_RIGHT)))
//	{
//		_position.x = _follow->GetPosition().x;
//	}*/
//}

//void Camera::SetTransform(Game* gDevice) const
//{
//	gDevice->getdevice()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
//	gDevice->getdevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
//	gDevice->getdevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
//}
