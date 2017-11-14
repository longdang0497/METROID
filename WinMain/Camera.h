#pragma once
#include <DirectXMath.h>
#include "Sprite.h"
#include "Game.h"

class GraphicsDevice;

class Camera
{
public:
	Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors);
	~Camera();

	void Update();
	void Follow(Sprite *following);
	void Unfollow();
	bool IsFollowing() const;
	//void SetTransform(Game *gDevice) const;

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

