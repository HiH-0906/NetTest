#include <DxLib.h>
#include "Pot.h"
#include <_DebugConOut.h>
#include <_DebugDispOut.h>
#include "FOLLOWER_TYPE.h"
#include "ENEMY_TYPE.h"
#include "func/PotNormal.h"
#include "func/PotHold.h"
#include "func/PotThrow.h"

Pot::Pot()
{
	Init();
}


Pot::~Pot()
{
}

void Pot::Update(std::vector<sharedObj>& objList)
{
	/*if (_mixList.empty())
	{
		return;
	}
	_comboCnt--;
	if (_comboCnt <= 0)
	{
		UNIT_ID checkID;
		int type;
		std::tie(checkID, type) = _mixList[0];
		switch (checkID)
		{
		case UNIT_ID::NON:
			break;
		case UNIT_ID::PLAYER:
			break;
		case UNIT_ID::ENEMY:
			lpSceneMng.AddInstanceQue({ UNIT_ID::FOLLOWER, static_cast<int>(FOLLOWER_TYPE::OCTOPUS),{ 500.0,400.0 },0});
			break;
		case UNIT_ID::POT:
			break;
		case UNIT_ID::FOLLOWER:
			lpSceneMng.AddInstanceQue({ UNIT_ID::ENEMY, static_cast<int>(ENEMY_TYPE::GHOST),{ 500.0,400.0 },0});
			break;
		default:
			break;
		}
		_comboCnt = COMBO_TIME;
		_mixList.clear();
	}*/

	try
	{
		_funcState[state()](*this, objList);
	}
	catch (...)
	{
		AST();
	}
}

void Pot::AddMixList(MixData data)
{
	_mixList.emplace_back(data);
}

void Pot::SetComboCnt(void)
{
	_comboCnt = COMBO_TIME;
}

void Pot::Init(void)
{
	// ----------アニメーション登録開始
	AnimVector data;

	ImageKey key = { IMG::POT,STATE::NORMAL };

	data.emplace_back(IMAGE_ID(key)[0], 30);
	data.emplace_back(IMAGE_ID(key)[0], 60);

	SetAnim({ STATE::NORMAL,DIR::DOWN }, data);

	data.emplace_back(IMAGE_ID(key)[0], 30);
	data.emplace_back(IMAGE_ID(key)[0], 60);

	SetAnim({ STATE::HOLD,DIR::DOWN }, data);

	data.emplace_back(IMAGE_ID(key)[0], 30);
	data.emplace_back(IMAGE_ID(key)[0], 60);

	SetAnim({ STATE::THROW,DIR::DOWN }, data);

	_unitID = UNIT_ID::POT;
	_team = TEAM_TAG::ALLY_TEAM;
	_searchRange = 40.0;
	_weight = 10;
	_pos = lpSceneMng.WorldCenter;
	_size = { 128,148 };
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);
	_speed = 0.0;
	_comboCnt = COMBO_TIME;

	// AddInstanceを通らずにインスタンスされるので通し番号を足しておく
	_serialNum = lpSceneMng.serialNumCnt();
	lpSceneMng.AddSerialNum();

	_funcState = { {STATE::NORMAL,PotNormal()},{STATE::HOLD,PotHold()},{STATE::THROW,PotThrow()} };


	// 初期アニメーション
	dir(DIR::DOWN);
	state(STATE::NORMAL);
}

void Pot::InitFunc(void)
{
}
