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

std::map<FOLLOWER_TYPE, std::function<bool(Obj&)>> Follower::followerInitMap = { 
	{FOLLOWER_TYPE::OCTOPUS, OctpusInit()} , 
	{FOLLOWER_TYPE::BEE, BeeInit()}, 
	{FOLLOWER_TYPE::DAEMON, FollowDemonInit()}, 
	{FOLLOWER_TYPE::GHOST, FollowGhostInit()}, 
	{FOLLOWER_TYPE::MUSH, FollowMushInit()} 
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
	// 自分からの距離が近い順にobjListをソート
	std::sort(objList.begin(), objList.end(),
		[&](sharedObj objA, sharedObj objB) {
		return LengthSquare((*objA).pos(), _pos) < LengthSquare((*objB).pos(), _pos);
	});

	(*_input).SetOld();
	(*_input).StateReset();

	if (state() == STATE::NORMAL)
	{
		(*_input).Update(objList);
	}

	if ((*_input).btnState(INPUT_ID::BTN_B).first && !(*_input).btnState(INPUT_ID::BTN_B).second)
	{

	}

	try
	{
		_funcState[state()](*this, objList);
	}
	catch (...)
	{
		AST();
	}
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

	_unitID = UNIT_ID::FOLLOWER;
	_team = TEAM_TAG::ALLY_TEAM;
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);
	_weight = 1;

	// 初期アニメーション
	state(STATE::NORMAL);
	dir(DIR::DOWN);
}
