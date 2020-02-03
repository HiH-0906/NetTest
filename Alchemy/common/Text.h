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

	// �w��̕�����������̃X�N���[���ɕ`�悷��
	// �S�p�����̂�
	void MakeText(const std::string&);
	bool isDraw(void);
	void LoadFontImg(void);
	int screen(void);
private:
	int _screen;	// �����`��p�̃X�N���[��
	bool _isDraw;	// �`�悳��Ă��邩
	static int _fontImg[FONT_DIV_CNT_Y][FONT_DIV_CNT_X];
};

