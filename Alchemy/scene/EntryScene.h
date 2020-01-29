#pragma once
#include "BaseScene.h"
#include "SceneMng.h"
#include <object/Obj.h>
#include <Input/InputState.h>
#include<object/PlNum.h>
#include<vector>

class EntryScene :
	public BaseScene
{
public:
	EntryScene();
	~EntryScene();

	UniqueBase Update(UniqueBase own)override;

private:
	void Init(void);
	void DrawInit(void);

	int _padnum;								 // �ڑ�����pad��
	int _entryPadnum;							 // �G���g���[����pad��

	int _entrnum[4];							// �G���g���[�����ԍ���ۑ������`��

	int _entryBG;								// �G���g���[�w�i
	int _padImage[4];							// �ڑ��ςݖ��o�^��PAD
	int _entryImage[4];							// ����L�����̐F��\���摜


	std::shared_ptr<InputState> _input[4];		// ���͊Ǘ��N���X

	/*std::vector<std::shared_ptr<InputState>> _input;*/
};

