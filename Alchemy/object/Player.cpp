#include <algorithm>
#include <_DebugConOut.h>
#include "Player.h"
#include <Input/PadState.h>
#include <Input/NetState.h>
#include <Scene/SceneMng.h>
#include <Camera.h>
#include "NetWork/NetWork.h"
#include "func/PlayerNormal.h"
#include "func/PlayerHold.h"
#include "func/PlayerThrow.h"

Player::Player()
{
	_input = std::make_unique<PadState>(DX_INPUT_PAD1);
	_plNum = PlNum::PL_01;
	_pos = {1080.0,800.0};

	Init();
}

Player::Player(PlNum plNum, Vector2Dbl pos, int padNum,sharedObj potObj)
{
	_input = std::make_unique<PadState>(padNum);
	_plNum = plNum;
	_pos = pos;
	_potObj = potObj;

	Init();
}

Player::Player(PlNum plNum, Vector2Dbl pos, sharedObj potObj)
{
	_input = std::make_unique<NetState>(plNum);
	_plNum = plNum;
	_pos = pos;
	_potObj = potObj;

	Init();
}

void Player::Update(std::vector<sharedObj>& objList)
{
	(*_input).Update(objList);
	_tageObj.reset();
	
	// 自分からの距離が近い順にobjListをソート
	std::sort(objList.begin(), objList.end(), 
		[&](sharedObj objA,sharedObj objB){
			return LengthSquare((*objA).pos(), _pos) < LengthSquare((*objB).pos(), _pos);
		});

	// 移動
	if ((*_input).LStickState().first.isInput)
	{
		_rad = RAD(static_cast<double>((*_input).LStickState().first.angle));
		_pos += {_speed * cos(_rad), _speed * sin(_rad)};

		dir((*_input).LStickState().first.dir);
	}

	try
	{
		_funcState[state()](*this, objList);
	}
	catch (...)
	{
		AST();
	}

	// targetが設定されているときはそいつを光らせる
	if (!_tageObj.expired())
	{
		(*_tageObj.lock()).glowFlag(true);
	}
	//lpNetWork.MakeMatchMes(_pos);
}

PlNum Player::plNum(void)
{
	return _plNum;
}

int Player::holdWeightMax(void)
{
	return _holdWeightMax;
}


Player::~Player()
{
}

void Player::Init(void)
{
	// ----------アニメーション登録開始
	AnimVector data;

	ImageKey key = { IMG::PLAYER,STATE::NORMAL };

	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4], 10);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 1], 20);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 2], 30);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 3], 40);

		SetAnim({ STATE::NORMAL,dir }, data);
	}

	// 投げ画像がまだないので一旦NORMAL
	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4], 10);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 1], 20);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 2], 30);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 3], 40);

		SetAnim({ STATE::THROW,dir }, data);
	}

	key.second = STATE::HOLD;

	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4], 10);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 1], 20);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 2], 30);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 3], 40);

		SetAnim({ STATE::HOLD,dir }, data);
	}
	
	_unitID = UNIT_ID::PLAYER;
	_team = TEAM_TAG::ALLY_TEAM;
	_searchRange = 40.0;
	_weight = 10;
	_holdWeightMax = 5;
	_throwRange = 300.0;
	_serialNum = lpSceneMng.serialNumCnt();
	lpSceneMng.AddSerialNum();

	_speed = 4.0;
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);

	_funcState = { {STATE::NORMAL,PlayerNormal()},{STATE::HOLD,PlayerHold()},{STATE::THROW,PlayerThrow()} };

	_pos = { 1080.0,800.0 };

	_hp = 10;


	// 初期アニメーション
	state(STATE::NORMAL);
	dir(DIR::DOWN);
}
