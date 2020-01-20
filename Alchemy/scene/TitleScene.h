#pragma once
#include "BaseScene.h"
#include <object/Obj.h>
#include <Input/InputState.h>
#include<common/DIR.h>

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	UniqueBase Update(UniqueBase own)override;

private:
	void Init(void);
	void TitleSelect(void);
	void DrawInit(void);

	int _titleBG;
	int _endBG;
	int _cursor;
	int _selectTex;
	int _titleTex;

	Vector2Dbl _cursorPos;

	bool _selectFlag;							//�Z���N�g�ڍs�t���O

	int _padnum;								//�ڑ�����pad��

	int _selectnum;								//�Z���N�g�p�ϐ�

	std::shared_ptr<InputState> _input[4];		// ���͊Ǘ��N���X
	
	bool startFlag;								//�V�[���ڍs�t���O
	bool endFlag;								//�Q�[���I���t���O

};

