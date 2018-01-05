#include "Sprite.h"
#include <vector>

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, LPWSTR Coord, int Width, int Height, int Count, int SpritePerRow)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	//Default the sprite to position (0, 0, 0)
	position.x = 0;
	position.y = 0;
	position.z = 0;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;
	_Coord = Coord;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(NULL, L"[ERROR] Failed to get information from image file.", FilePath, NULL);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		MessageBox(NULL, L"[ERROR] Failed to create texture from file.", NULL, NULL);
		return;
	}
}

RECT Sprite::ReadCoord()
{
	int ** coord = new int*[2];	//init array Sprite's position

	//Read file info of file
	fstream f;
	try
	{
		f.open(_Coord);
	}
	catch (std::fstream::failure e)
	{
		MessageBox(NULL, L"[Sprite class]--Read sprite info from file failed", L"Error", NULL);
	}
	string line;
	int id = 0;
	while (!f.eof() && id < _Count)
	{
		vector<string> pos;
		string split;
		getline(f, line);
		istringstream iss(line);

		while (getline(iss, split, '\t'))
		{
			pos.push_back(split);
		}

		coord[id] = new int[_Count];

		coord[id][0] = stoi(pos[0]);
		srect.left = coord[id][0];

		coord[id][1] = stoi(pos[1]);
		srect.top = coord[id][1];

		srect.right = srect.left + _Width;
		srect.bottom = srect.top + _Height + 1;

		if (id == _Index)
		{
			break;
		}

		id++;
	}
	f.close();

	

	////read info from file
	//ifstream f;
	//try {
	//	if (_Coord != NULL) f.open(_Coord);
	//	for (int i = 0; i < _Count; i++)
	//	{
	//		if (!f.eof())
	//		{
	//			
	//			f >> coord[i][0];
	//			if (coord[i][0] != '\t' && coord[i][0] != '\n') srect.left = coord[i][0];
	//			f >> coord[i][1];
	//			if (coord[i][1] != '\t' && coord[i][1] != '\n') srect.top = coord[i][1];
	//			
	//		}

	//		if (i == _Index)
	//		{
	//			break;
	//		}
	//	}
	//	f.close();
	//}
	//catch (std::fstream::failure e) {}
	return srect;
}

int Sprite::GetIndex()
{
	return _Index;
}

void Sprite::SetIndex(int value)
{
	_Index = value;
}

void Sprite::Next()
{
	_Index = (_Index + 1) % _Count;
}

void Sprite::Reset()
{
	_Index = 0;
}

void Sprite::Render(float X, float Y)
{
	RECT rec_sprite = ReadCoord();
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	position.x = X;
	position.y = Y;

	//
	// convert position in world to position in camera
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);	//Làm sạch ma trận (biến nó về lại ma trận đồng nhất).
	mt._22 = -1.0f;
	mt._41 = (float)-Camera::_curCamX;;
	mt._42 = Camera::_curCamY;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, -vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	/*D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, 1.5, 1.5, 1);
	_SpriteHandler->SetTransform(&mt1);*/

	_SpriteHandler->Draw(
		_Image,
		&rec_sprite,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255));
}

Sprite::~Sprite()
{
	_Image->Release();
}
