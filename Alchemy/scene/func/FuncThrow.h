#pragma once
#include "../GameScene.h"

#define THROW_CNT_MAX 30.0			// 投げてから着地までの時間
#define THROW_INITIAL_SPEED 15.0	// 投げの初速、_velを設定する時の大きさ

// Playerが物を投げるときの処理
struct FuncThrow
{
	bool operator()(ActQueT&, std::vector<sharedObj>&);
};

