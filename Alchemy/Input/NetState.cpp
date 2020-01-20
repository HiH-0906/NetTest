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
	// ү���ގ��o���p�ϐ��쐬 ү���ނȂ������ꍇ�̂��߂�Old���
	auto state = LStickState().second;
	// ү���ގ擾
	auto mes = lpNetWork.GetMes(_plNum, MES_TYPE::KEY);
	// �擾����ү���ނ�Key��񂩂ǂ���
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
		// ү���ނ��Ȃ������ꍇOld����
		for (auto id : INPUT_ID())
		{
			btnState(id, btnState(id).second);
		}
	}
	LStickState(state);
}
