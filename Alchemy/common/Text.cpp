#include <DxLib.h>
#include <ImageMng.h>
#include "Text.h"

int Text::_fontImg[FONT_DIV_CNT_Y][FONT_DIV_CNT_X];

Text::Text()
{
	_isDraw = false;
}


Text::~Text()
{
}

void Text::MakeText(const std::string& str)
{
	_size = { FONT_SIZE_X * (static_cast<int>(str.size()) / 2), FONT_SIZE_Y };
	_screen = MakeScreen(FONT_SIZE_X * (static_cast<int>(str.size()) / 2), FONT_SIZE_Y, true);
	SetDrawScreen(_screen);
	ClsDrawScreen();

	int x, y;
	for (int i = 0; i < static_cast<int>(str.size()); i+= 2)
	{
		if (str[i + 1] < 0)
		{
			x = static_cast<int>(str[i + 1] + 192) % FONT_DIV_CNT_X;
			y = (static_cast<int>(str[i]) + 126) * 12 + ((static_cast<int>(str[i + 1]) + 192) / FONT_DIV_CNT_X);
		}
		else
		{
			x = static_cast<int>(str[i + 1] -64) % FONT_DIV_CNT_X;
			y = (static_cast<int>(str[i]) + 126) * 12 + ((static_cast<int>(str[i + 1]) -64) / FONT_DIV_CNT_X);
		}
		
		DrawGraph(FONT_SIZE_X * i / 2, 0, _fontImg[y][x],true);
	}

	_isDraw = true;
}

void Text::MakeText(const std::string& str, int space)
{
	_size = { FONT_SIZE_X * (static_cast<int>(str.size()) / 2) - (space * (static_cast<int>(str.size()) / 2 - 1)), FONT_SIZE_Y };
	_screen = MakeScreen(_size.x, _size.y, true);
	SetDrawScreen(_screen);
	ClsDrawScreen();

	int x, y;
	for (int i = 0; i < static_cast<int>(str.size()); i += 2)
	{
		if (str[i + 1] < 0)
		{
			x = static_cast<int>(str[i + 1] + 192) % FONT_DIV_CNT_X;
			y = (static_cast<int>(str[i]) + 126) * 12 + ((static_cast<int>(str[i + 1]) + 192) / FONT_DIV_CNT_X);
		}
		else
		{
			x = static_cast<int>(str[i + 1] - 64) % FONT_DIV_CNT_X;
			y = (static_cast<int>(str[i]) + 126) * 12 + ((static_cast<int>(str[i + 1]) - 64) / FONT_DIV_CNT_X);
		}

		DrawGraph((FONT_SIZE_X  + space )* i / 2, 0, _fontImg[y][x], true);
	}

	_isDraw = true;
}

bool Text::isDraw(void)
{
	return _isDraw;
}

void Text::LoadFontImg(void)
{
	lpImageMng.GetID({ IMG::FONT ,STATE::NORMAL }, "image/font.png", { FONT_SIZE_X,FONT_SIZE_X }, { FONT_DIV_CNT_X,FONT_DIV_CNT_Y });

	for (int y = 0; y < FONT_DIV_CNT_Y; y++)
	{
		for (int x = 0; x < FONT_DIV_CNT_X; x++)
		{
			_fontImg[y][x] = lpImageMng.GetID({ IMG::FONT ,STATE::NORMAL })[y * FONT_DIV_CNT_X + x];
		}
	}
}

int Text::screen(void)
{
	return _screen;
}

Vector2Int& Text::size(void)
{
	return _size;
}
