#pragma once
#include <string>
#include <Vector2.h>

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

	// �w��̕�����������̃X�N���[���ɕ`�悷��
	// �S�p�����̂�
	// string:�`�悵��������,space:�s��
	void MakeText(const std::string&,int space);
	bool isDraw(void);
	void LoadFontImg(void);
	int screen(void);
	Vector2Int& size(void);
private:
	int _screen;	// �����`��p�̃X�N���[��
	Vector2Int _size;		// �X�N���[���̃T�C�Y
	bool _isDraw;	// �`�悳��Ă��邩
	static int _fontImg[FONT_DIV_CNT_Y][FONT_DIV_CNT_X];
};

