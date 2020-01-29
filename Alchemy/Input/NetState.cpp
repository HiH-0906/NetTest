#include "NetState.h"


NetState::NetState(PlNum plNum)
{
	_plNum = plNum;
	_num = 0;
}

NetState::~NetState()
{
}

void NetState::Update(std::vector<sharedObj>& objList)
{
	SetOld();
	// ﾒｯｾｰｼﾞ取り出し用変数作成 ﾒｯｾｰｼﾞなかった場合のためのOld代入
	auto state = LStickState().second;
	// ﾒｯｾｰｼﾞ取得
	auto mes = lpNetWork.GetMes(_plNum, MES_TYPE::KEY);
	tmp.emplace_back(mes);
	if (tmp.size()>=256)
	{
		AST();
	}
	// 取得したﾒｯｾｰｼﾞがKey情報かどうか
	if (static_cast<MES_TYPE>(mes.check.type) == MES_TYPE::KEY)
	{
		TRACE("%d\n", mes.key.num);
		_num++;
		btnState(INPUT_ID::BTN_A,mes.key.a);
		btnState(INPUT_ID::BTN_B, mes.key.b);
		btnState(INPUT_ID::BTN_Y, mes.key.y);
		if (mes.key.lf)
		{
			state.isInput = true;
			state.angle = mes.key.ls;
			state.dir = convToDir(mes.key.ls);
		}
		else
		{
			state.isInput = false;
			state.isInput = 0;
			state.dir = DIR::DOWN;
		}
	}
	else
	{
		// ﾒｯｾｰｼﾞがなかった場合Oldを代入
		for (auto id : INPUT_ID())
		{
			btnState(id, btnState(id).second);
		}
	}
	LStickState(state);
}
