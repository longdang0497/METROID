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
	~Camera();

	void Update();
	void Follow(Sprite *following);
	void Unfollow();
	bool IsFollowing() const;
private:
	float _angle;
	DirectX::XMFLOAT3 _scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;		

	Sprite *_following;

	int _width;
	int _height;
};

