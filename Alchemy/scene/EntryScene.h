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

	int _padnum;								 //接続中のpad数
	int _entryPadnum;							 //ｴﾝﾄﾘｰしたpad数

	int _entrnum[4];							//エントリーした番号を保存するや～つ

	std::shared_ptr<InputState> _input[4];		// 入力管理クラス

	bool _entryFlag[4];

	/*std::vector<std::shared_ptr<InputState>> _input;*/
};

