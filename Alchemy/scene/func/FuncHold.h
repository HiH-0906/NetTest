#pragma once
#include "../GameScene.h"

// Playerが物を持つときの処理
struct FuncHold
{
	bool operator()(ActQueT&, std::vector<sharedObj>&);

};