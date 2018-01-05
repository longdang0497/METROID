#include "TextSprite.h"

TextSprite::TextSprite(LPWSTR text, D3DXVECTOR2 position, LPD3DXSPRITE spriteHandle)
{
	object = new Sprite(spriteHandle, FONT, NULL, FONT_SIZE, FONT_SIZE, 1, 1);
	_position = position;
	_text = text;
}

TextSprite::~TextSprite()
{
}

D3DXVECTOR2 TextSprite::getPosition()
{
	return _position;
}

void TextSprite::setPosition(D3DXVECTOR2 position)
{
	_position = position;
}

void TextSprite::setText(LPWSTR text)
{
	_text = text;
}

void TextSprite::_DrawText(LPD3DXSPRITE spriteHandle)
{
	int index = 0;
	int array;
	char c = NULL;
	wchar_t* value = _text;
	char* txt = new char[wcslen(_text)];
	array = wcstombs(txt, _text, wcslen(_text));

	if (array)
	{
		// Sprite đánh thứ tự index theo 0-based
		for (int j = 0; j < wcslen(value); j++)
		{
			c = txt[j];
			if (c >= 'A' && c <= 'Z')
			{
				// Thứ tự của char kể từ 'A'
				// VD: A => index = 0; B => index = 1
				index = ((int)c) - 'A';
			}
			else if (c >= 'a' && c <= 'z')
				index = ((int)c) - 'a';
			else if (c >= '0' && c <= '9')
				index = (((int)c) - '0') + 26;
			else if (c == '.')
				index = 36;
			else if (c == '!')
				index = 42;
			else if (c == '-')
				index = 44;
			else if (c == ':')
				index = 45;
			else if (c == ' ')
				index = 53;

			// Set index để lấy frameRect tương ứng muốn vẽ
			object->SetIndex(index);
			object->Render((_position.x + GetWidth() * j), _position.y);

			// Render tọa độ top-left
			//_sprite->render(spriteHandle);
		}
	}
}
