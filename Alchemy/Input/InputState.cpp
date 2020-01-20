#include <_DebugConOut.h>
#include "InputState.h"

InputState::InputState()
{
	// 入力キーの設定
	KeyPair pair = { 0,1 };
	for (auto id : INPUT_ID())
	{
			_btnState.try_emplace(id, pair);
	}

	_LStickState.first = { false,90,DIR::DOWN };
	_LStickState.second = { true,90,DIR::DOWN };
}

InputState::~InputState()
{
}

// キーマップごと取得
const KeyMap & InputState::btnState(void) const
{
	return _btnState;
}

// 指定したキーの押下状態だけ取得
const KeyPair & InputState::btnState(INPUT_ID id) const
{
	static const KeyPair errorState = KeyPair(0, 0);		// エラー時に返す
	try 
	{
		return _btnState.at(id);
	}
	catch (...)
	{
		AST();
		return errorState;
	}
}

// キー状態設定
bool InputState::btnState(INPUT_ID id,char inputData)
{
	if (_btnState.find(id) != _btnState.end())
	{
		_btnState[id].first = inputData;
		return true;
	}
	
	return false;
}

const StickPair & InputState::LStickState(void)
{
	return _LStickState;
}

void InputState::LStickState(StickState& inputData)
{
	_LStickState.first = std::move(inputData);
}

void InputState::StateReset(void)
{
	for (auto id : INPUT_ID())
	{
		btnState(id, 0);
	}
	StickState state = { false,0,DIR::DOWN };
	LStickState(state);
}

// 入力キーのold状態更新
void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			// first  : now
			// second : old
			_btnState[id].second = _btnState[id].first;
		}
		catch(...)
		{
			AST();
			_btnState.emplace(id, KeyPair{ 0,1 });
		}
	}

	_LStickState.second = _LStickState.first;
}

