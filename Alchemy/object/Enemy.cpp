#include <algorithm>
#include <_DebugConOut.h>
#include "Enemy.h"
#include <Input/PadState.h>
#include <Input/AI/enemyAI.h>
#include "Enemy_Init\SlimeInit.h"
#include "Enemy_Init\BatInit.h"
#include "Enemy_Init\GhostInit.h"
#include "Enemy_Init\MushroomInit.h"
#include "Enemy_Init\DemonInit.h"


std::map<ENEMY_TYPE, std::function<bool(Obj&)>> Enemy::enemyInitMap = { {ENEMY_TYPE::SLIME,SlimeInit()},{ ENEMY_TYPE::BAD,BatInit() },{ ENEMY_TYPE::MUSH,MushroomInit() },{ ENEMY_TYPE::DAEMON,DemonInit() },{ ENEMY_TYPE::GHOST,GhostInit() } };

Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(EnemyState enemyState, sharedObj potObj)
{
	std::tie(_enemyType, _pos, _serialNum) = enemyState;
	_potObj = potObj;
	Init();
}

void Enemy::Update(std::vector<sharedObj>& objList)
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
		if ((*_input).btnState(INPUT_ID::BTN_B).first && !((*_input).btnState(INPUT_ID::BTN_B).second))
		{
			
			state(STATE::ATTACK);
		}
	}

	try
	{
		_funcState[state()](*this,objList);
	}
	catch (...)
	{
		AST();
	}
}

const ENEMY_TYPE Enemy::enemyType(void) const
{
	return _enemyType;
}

int Enemy::getType(void)
{
	return static_cast<int>(_enemyType);
}

Enemy::~Enemy()
{
}

void Enemy::Init(void)
{
	try
	{
		enemyInitMap[_enemyType](*this);
	}
	catch (...)
	{
		AST();
	}
	

	_weight = 1;
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);
	_unitID = UNIT_ID::ENEMY;
	_team = TEAM_TAG::ENEMY_TEAM;

	// 初期アニメーション
	state(STATE::NORMAL);
	dir(DIR::DOWN);
}


