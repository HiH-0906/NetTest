#include "NetState.h"
#include "../NetWork/NetWork.h"

NetState::NetState(PlNum plNum)
{
	_plNum = plNum;
}

NetState::~NetState()
{
}

void NetState::Update(std::vector<sharedObj>& objList)
{
	SetOld();
	// Ò¯¾°¼Şæ‚èo‚µ—p•Ï”ì¬ Ò¯¾°¼Ş‚È‚©‚Á‚½ê‡‚Ì‚½‚ß‚ÌOld‘ã“ü
	auto state = LStickState().second;
	// Ò¯¾°¼Şæ“¾
	auto mes = lpNetWork.GetMes(_plNum, MES_TYPE::KEY);
	// æ“¾‚µ‚½Ò¯¾°¼Ş‚ªKeyî•ñ‚©‚Ç‚¤‚©
	if (static_cast<MES_TYPE>(mes.check.type) == MES_TYPE::KEY)
	{
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
		// Ò¯¾°¼Ş‚ª‚È‚©‚Á‚½ê‡Old‚ğ‘ã“ü
		for (auto id : INPUT_ID())
		{
			btnState(id, btnState(id).second);
		}
	}
	LStickState(state);
}
