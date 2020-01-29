#pragma once
#include <map>
#include "INPUT_ID.h"
#include <Vector2.h>
#include <object\Obj.h>
#include <DIR.h>

using KeyPair = std::pair<char, char>;
using KeyMap = std::map<INPUT_ID, KeyPair>;

struct StickState
{
	bool isInput;		// 入力があるか
	short angle;		// スティックの角度
	DIR dir;			// 八方向にしたときの向き
};

using StickPair = std::pair<StickState, StickState>;

class InputState
{
public:
	InputState();

	virtual ~InputState();

	const KeyMap& btnState(void)const;					// キーマップごと取得
	const KeyPair & btnState(INPUT_ID id)const;			// 指定したキーの押下状態だけ取得
	bool btnState(INPUT_ID id, char inputData);			// キー状態設定

	const StickPair& LStickState(void);
	void LStickState(StickState& inputData);
	void StateReset(void);

	void SetOld(void);									// キーのold状態更新
	virtual void Update(std::vector<sharedObj>& objList) = 0;

private:
	KeyMap _btnState;									// 入力可能キーの押下状態,first:new,second:old
	StickPair _LStickState;								// 左スティックの入力状態,first:new,second:old
};