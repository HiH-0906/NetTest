#pragma once
#include "object/Obj.h"

#define BOSS_CNT_MAX 120.0

class Boss :
	public Obj
{
public:
	Boss();
	Boss(sharedObj potObj);
	~Boss();
	void Update(std::vector<sharedObj>& objList) override;

private:
	void Init();
	bool AddBossMove();					// ｲﾝｽﾀﾝｽされて出現するときの動き
	void DrawHP(void)override;			// Hp描画用

	int _bossHPImg[3];					// ﾎﾞｽのHP画像用
	Vector2Dbl _endPos;					// 終点格納
	int _addCnt;						// 出現ｶｳﾝﾄ
	double _addVec;						// 出現時のｽﾋﾟｰﾄﾞ
	bool _addFlag;						// 出現時用ﾌﾗｸﾞ
};

