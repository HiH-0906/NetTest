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

	bool _selectFlag;							//セレクト移行フラグ

	int _padnum;								//接続中のpad数

	int _selectnum;								//セレクト用変数

	std::shared_ptr<InputState> _input[4];		// 入力管理クラス
	
	bool startFlag;								//シーン移行フラグ
	bool endFlag;								//ゲーム終了フラグ

};

