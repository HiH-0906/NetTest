#pragma once
#include "../GameScene.h"

// Playerが物をその場に置く時処理
struct FuncPut
{
	bool operator()(ActQueT&, std::vector<sharedObj>&);

};
