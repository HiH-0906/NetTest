#include <Dxlib.h>
#include <_DebugConOut.h>
#include <EffectMng.h>
#include "../Map.h"
#include "Boss.h"
#include <input/InputState.h>
#include <Input/Enemy_AI/Boss_AI.h>
#include "func/TestEnemyUpdate.h"
#include "func/BossAttack.h"

Boss::Boss()
{
	Init();
}

Boss::~Boss()
{
}

void Boss::Update(std::vector<sharedObj>& objList)
{
	if (DestroyProc())
	{
		return;
	}

	if (state() == STATE::NORMAL)
	{
		if (lpSceneMng.frameCnt() % 2)
		{
			(*_input).SetOld();
			(*_input).StateReset();

			(*_input).Update(objList);
			if ((*_input).btnState(INPUT_ID::BTN_B).first)
			{
				_effectFlg = false;
				state(STATE::ATTACK);
			}
		}
	}

	try
	{
		_funcState[state()](*this, objList);
	}
	catch (...)
	{
		AST();
	}

	lpMap.ChangeChip(_pos, _rad, 0);

	// 死亡
	if (_hp <= 0)
	{
		alive(false);
	}

	_zOrder = static_cast<int>(_height);
}

void Boss::Init()
{
	AnimVector data;

	ImageKey key = { IMG::BOSS, STATE::NORMAL };

	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4], 10);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 1], 20);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 2], 30);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 3], 40);
		SetAnim({ STATE::NORMAL, dir }, data);
	}

	// 攻撃用ダミー画像
	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4], 10);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 1], 20);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 2], 30);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 3], 40);
		SetAnim({ STATE::ATTACK,dir }, data);
	}

	// 死んだとき
	key = { IMG::BLAST, STATE::DEATH };
	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		for (int i = 0; i < 10; i++)
		{
			data.emplace_back(IMAGE_ID(key)[i], i * 3);
		}
		data.emplace_back(-1, 33);
		SetAnim({ STATE::DEATH,dir }, data);
	}

	_attackRange = 200.0;
	_searchRange = 200.0;
	_speed = 0.5;

	_hpMax = 100;
	_hp = _hpMax;

	_team = TEAM_TAG::ENEMY_TEAM;
	_unitID = UNIT_ID::ENEMY;

	_coolCntMax = 100;
	_coolCnt = _coolCntMax;

	_input = std::make_unique<Boss_AI>(*this);

	_weight = INT_MAX;
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);
	_effectScreen = MakeScreen(static_cast<int>(lpEffectMng._screenSize.x), static_cast<int>(lpEffectMng._screenSize.y), true);

	_funcState = { {STATE::NORMAL, TestEnemyUpdate()}, {STATE::ATTACK, BossAttack()} };

	// 初期アニメーション
	state(STATE::NORMAL);
	dir(DIR::DOWN);
}
