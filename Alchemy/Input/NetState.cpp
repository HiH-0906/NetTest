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
	if (!lpNetWork.Active())
	{
		return;
	}
	SetOld();
	// ﾒｯｾｰｼﾞ取り出し用変数作成 ﾒｯｾｰｼﾞなかった場合のためのOld代入
	auto state = LStickState().second;
	// ﾒｯｾｰｼﾞ取得
	lpNetWork.GetKey(_keyBuf, _plNum);
	if (_keyBuf.size() == 0 || _keyBuf.size() <= _num)
	{
		return;
	}
	TRACE("%d\n", _num);
	/*if (_keyBuf[_num].key.num != _num)
	{
		lpNetWork.MakeAgainMes(_plNum, _num);
		return;
	}*/
	btnState(INPUT_ID::BTN_A, _keyBuf[_num].key.a);
	btnState(INPUT_ID::BTN_B, _keyBuf[_num].key.b);
	btnState(INPUT_ID::BTN_Y, _keyBuf[_num].key.y);
	btnState(INPUT_ID::BTN_LB, _keyBuf[_num].key.lb);
	btnState(INPUT_ID::BTN_RB, _keyBuf[_num].key.rb);
	btnState(INPUT_ID::LEFT_TRIGGER, _keyBuf[_num].key.lt);
	btnState(INPUT_ID::RIGHT_TRIGGER, _keyBuf[_num].key.rt);
	if (_keyBuf[_num].key.lf)
	{
		state.isInput = true;
		state.angle = _keyBuf[_num].key.ls;
		state.dir = convToDir(_keyBuf[_num].key.ls);
	}
	else
	{
		state.isInput = false;
		state.isInput = 0;
		state.dir = DIR::DOWN;
	}
	LStickState(state);
	_num++;
}
