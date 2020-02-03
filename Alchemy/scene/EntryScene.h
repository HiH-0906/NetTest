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
	void EntryStart(void);
	void EntryNormal(void);

	void (EntryScene::*func)(void);

	int _padnum;								 // 接続中のpad数
	int _entryPadnum;							 // エントリーしたpad数

	int _entrnum[4];							// エントリーした番号を保存するや～つ

	int _entryBG;								// エントリー背景
	int _backImage[4];							// 接続済み未登録の背景
	int _entryImage[4][4];						// 操作キャラを表す画像
	int _skyimage;								// 背景・空

	int _fadecolor;								// フェードの数値
	int _fadespeed;								// フェード速度
	int _cnt[4];								// ﾌﾚｰﾑｶｳﾝﾄ


	std::shared_ptr<InputState> _input[4];		// 入力管理クラス

	/*std::vector<std::shared_ptr<InputState>> _input;*/
};

