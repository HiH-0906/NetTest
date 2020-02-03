#pragma once
#include "BaseScene.h"
#include <object/Obj.h>
#include <Input/InputState.h>
#include<common/DIR.h>

enum class SELECTMENU
{
	START,
	END,
	MAX
};



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
	void TitleEnd(void);
	void TitleNormal(void);
	void NEXT(void);

	void (TitleScene::*func)(void);

	int _titleLogo;								// タイトルロゴ
	int _titleBG;								// 通常タイトル背景
	int _cursor;								// カーソル画像
	int _selectTex;								// GAME START,GAME END
	int _titleTex;								// PLEES START
	int _skyimage[2];							// 背景・空

	Vector2Dbl T_logoPos;						// タイトルロゴの座標
	Vector2Dbl _skyPos[2];						// 空の座標
	Vector2Dbl _cursorPos;						// カーソル位置座標

	int _padnum;								// 接続中のpad数

	double _fallSpeed;							// セレクトメニューの移動速度
	int _cnt;									// ﾌﾚｰﾑｶｳﾝﾄ
	int _fadecolor;								// フェードの数値
	int _fadespeed;								// フェード速度

	SELECTMENU _selectnum;						// セレクト内容

	std::shared_ptr<InputState> _input[4];		// 入力管理クラス

};

