#pragma once
// オブジェクトの状態
enum class STATE
{
	NORMAL,		// 通常
	HOLD,		// 持っている
	THROW,		// 投げ
	HOLDEN,		// 持たれている
	THROWN,		// 投げられている
	ATTACK,		// 攻撃
	DEATH,		// 死
	MAX,
};


STATE begin(STATE);
STATE end(STATE);

STATE operator++(STATE type);
STATE operator*(STATE type);
