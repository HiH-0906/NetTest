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

	int _padnum;								 //�ڑ�����pad��
	int _entryPadnum;							 //���ذ����pad��

	int _entrnum[4];							//�G���g���[�����ԍ���ۑ������`��

	std::shared_ptr<InputState> _input[4];		// ���͊Ǘ��N���X

	bool _entryFlag[4];

	/*std::vector<std::shared_ptr<InputState>> _input;*/
};

