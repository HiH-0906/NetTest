#pragma once
#include <vector>
#include "../Obj.h"

class Player;

struct PlayerHold
{
	void operator()(Obj&, std::vector<sharedObj>& objList);
private:
	// 持ち物入れ替え移動
	void ExchangeMove(Player&);

	bool _exChange;		// 持ち物入れ替え時の特殊移動ﾌﾗｸﾞ
	int _changeNum;		// 入れ替えてるオブジェクトの格納場所
	int _moveCnt;		// 入れ替え移動のカウント
	std::vector<std::pair<double,double>> _heightList;	// 入れ替え前後の高さを持つ、格納場所は入れ替え後のholdListと対応している
};
