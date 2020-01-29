#pragma once
#include "BaseScene.h"
#include <object/Obj.h>
#include <Input/InputState.h>

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	UniqueBase Update(UniqueBase own)override;

private:

	void Init(void);
	void DrawInit(void);

	int _resultBG;							// �w�i
	int _resultLogo;
	int _resultTex;							// PLEES START

	int _cnt;								// �ڰѶ���

	std::shared_ptr<InputState> _input;		// ���͊Ǘ��N���X
};

