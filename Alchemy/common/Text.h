#pragma once
#include <string>

#define FONT_DIV_CNT_Y 18
#define FONT_DIV_CNT_X 16

#define FONT_SIZE_X 32
#define FONT_SIZE_Y 32

class Text
{
public:
	Text();
	~Text();

	// 指定の文字列を自分のスクリーンに描画する
	// 全角文字のみ
	void MakeText(const std::string&);
	bool isDraw(void);
	void LoadFontImg(void);
	int screen(void);
private:
	int _screen;	// 文字描画用のスクリーン
	bool _isDraw;	// 描画されているか
	static int _fontImg[FONT_DIV_CNT_Y][FONT_DIV_CNT_X];
};

