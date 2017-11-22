#pragma once
#include <DirectXMath.h>
#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"

class GraphicsDevice;

class Camera //: public GameObject
{
public:
	Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors);
	//Camera(GameObject* follow = NULL);
	~Camera();

	void Update();
	void Follow(Sprite *following);
	void Unfollow();
	bool IsFollowing() const;
	//void SetTransform(Game *gDevice) const;

	//static Camera* GetInstance();

	//void UpdateCam(float deltaTime);

	//bool IsInCamera(D3DXVECTOR2 position, int width, int height);

	//D3DXVECTOR2 ConvertPosition(D3DXVECTOR2 position);
	//D3DXVECTOR2 ConvertPosition(float x, float y);
private:
	float _angle;
	DirectX::XMFLOAT3 _scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	Sprite *_following;

	int _width;
	int _height;
//private:
//	static Camera* _instance;
//
//	RECT _mapRect;
//	GameObject* _follow;
};

