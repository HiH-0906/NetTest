#include <algorithm>
#include <_DebugConOut.h>
#include "Follower.h"
#include <Input/PadState.h>
#include <Input/AI/enemyAI.h>
#include "func/TestEnemyUpdate.h"
#include "func/HoldenUpdate.h"
#include "func/ThrownUpdate.h"
#include "Follower_Init/OctpusInit.h"
#include "Follower_Init/BeeInit.h"
#include "Follower_Init/FollowDemonInit.h"
#include "Follower_Init/FollowGhostInit.h"
#include "Follower_Init/FollowMushInit.h"
#include "Follower_Init/FollowPotInit.h"
#include <EffectMng.h>
#include "../Map.h"
#include "PlNum.h"

std::map<FOLLOWER_TYPE, std::function<bool(Obj&)>> Follower::followerInitMap = { 
	{FOLLOWER_TYPE::OCTOPUS, OctpusInit()} , 
	{FOLLOWER_TYPE::BEE, BeeInit()}, 
	{FOLLOWER_TYPE::DAEMON, FollowDemonInit()}, 
	{FOLLOWER_TYPE::GHOST, FollowGhostInit()}, 
	{FOLLOWER_TYPE::MUSH, FollowMushInit()},
	{FOLLOWER_TYPE::POT,FollowPotInit()}
};

Follower::Follower()
{
	Init();
}

Follower::Follower(FollowerState followerState, sharedObj potObj)
{
	std::tie(_followerType, _pos, _serialNum) = followerState;
	_potObj = potObj;
	Init();
}

void Follower::Update(std::vector<sharedObj>& objList)
{
	if (DestroyProc())
	{
		return;
	}


	if (state() == STATE::NORMAL)
	{
		if (lpSceneMng.frameCnt() % 2)
		{
			//// 自分からの距離が近い順にobjListをソート
			//std::sort(objList.begin(), objList.end(),
			//	[&](sharedObj objA, sharedObj objB) {
			//	return LengthSquare((*objA).pos(), _pos) < LengthSquare((*objB).pos(), _pos);
			//});
			//
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
	lpMap.ChangeChip(_pos, _rad, 2);

	// 死亡
	if (_hp <= 0)
	{
		alive(false);
	}

	_zOrder = static_cast<int>(_height);
}

int Follower::getType(void)
{
	return static_cast<int>(_followerType);
}

Follower::~Follower()
{
}

void Follower::Init(void)
{
	try
	{
		followerInitMap[_followerType](*this);
	}
	catch(...)
	{
		AST();
	}

	// ----------アニメーション登録開始
	AnimVector data;
	ImageKey death = { IMG::BLAST,STATE::DEATH };

	// 死んだとき
	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		for (int i = 0; i < 10; i++)
		{
			data.emplace_back(IMAGE_ID(death)[i], i * 3);
		}
		data.emplace_back(-1, 33);
		SetAnim({ STATE::DEATH,dir }, data);
	}

	_hp = _hpMax;
	_unitID = UNIT_ID::FOLLOWER;
	_team = TEAM_TAG::ALLY_TEAM;
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);
	_weight = 1;
	_coolCnt = _coolCntMax;
	_effectScreen = MakeScreen(static_cast<int>(lpEffectMng._screenSize.x), static_cast<int>(lpEffectMng._screenSize.y), true);

	// 初期アニメーション
	state(STATE::NORMAL);
	dir(DIR::DOWN);
}
