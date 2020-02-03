#include <_DebugConOut.h>
#include "PadState.h"
#include "../NetWork/NetWork.h"

PadState::PadState()
{
	_pudNum = DX_INPUT_PAD1;
}

PadState::PadState(int pudNum)
{
	_pudNum = pudNum;
}

PadState::~PadState()
{
}

void PadState::Update(std::vector<sharedObj>& objList)
{
	SetOld();

	XINPUT_STATE padState;
	if (GetJoypadXInputState(_pudNum, &padState) == -1)
	{
		AST();
	}
	
	for (auto id = begin(INPUT_ID()); id != INPUT_ID::LEFT_TRIGGER;++id)
	{
		btnState(id, padState.Buttons[static_cast<int>(id)]);
	}

	// Lトリガー
	if (padState.LeftTrigger > 200)
	{
		btnState(INPUT_ID::LEFT_TRIGGER, true);
	}
	else
	{
		btnState(INPUT_ID::LEFT_TRIGGER, false);
	}

	// Rトリガー
	if (padState.LeftTrigger > 200)
	{
		btnState(INPUT_ID::RIGHT_TRIGGER, true);
	}
	else
	{
		btnState(INPUT_ID::RIGHT_TRIGGER, false);
	}

	StickState state;

	if (abs(padState.ThumbLX) > 25000 || abs(padState.ThumbLY) > 25000)
	{
		state.isInput = true;
		state.angle = static_cast<short>DEG(atan2(static_cast<double>(-padState.ThumbLY), static_cast<double>(padState.ThumbLX)));

		state.dir = convToDir(state.angle);
	}
	else
	{
		state.isInput = false;
		state.angle = 0;
		state.dir = DIR::DOWN;
	}

	LStickState(state);

	// 送信用ﾃﾞｰﾀ作成
	lpNetWork.MakeKeyMes(btnState(), state);
}
