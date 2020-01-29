#include <algorithm>
#include <_DebugConOut.h>
#include "Player.h"
#include <Input/PadState.h>
#include <Input/NetState.h>
#include <Scene/SceneMng.h>
#include <Camera.h>
#include <Map.h>
#include "NetWork/NetWork.h"
#include "func/PlayerNormal.h"
#include "func/PlayerHold.h"
#include "func/PlayerThrow.h"
#include "func/PlayerDeath.h"

Player::Player()
{
	_input = std::make_unique<PadState>(DX_INPUT_PAD1);
	_plNum = PlNum::PL_01;
	_pos = {1080.0,800.0};
	_size = { 60,64 };

	Init();
}

Player::Player(PlNum plNum, Vector2Dbl pos, int padNum,sharedObj potObj)
{
	_input = std::make_unique<PadState>(padNum);
	_plNum = plNum;
	_pos = pos;
	_potObj = potObj;
	_size = { 60,64 };

	Init();
}

Player::Player(PlNum plNum, Vector2Dbl pos, sharedObj potObj)
{
	_input = std::make_unique<NetState>(plNum);
	_plNum = plNum;
	_pos = pos;
	_potObj = potObj;
	_size = { 60,64 };

	Init();
}

void Player::Update(std::vector<sharedObj>& objList)
{
	//　現段階では死なないほうがデバックしやすいので
	/*if (_hp <= 0)
	{
		dir(DIR::DOWN);
		state(STATE::DEATH);
	}
	else*/
	{
		(*_input).Update(objList);
		_tageObj.reset();

		// 自分からの距離が近い順にobjListをソート
		std::sort(objList.begin(), objList.end(),
			[&](sharedObj objA, sharedObj objB) {
			return LengthSquare((*objA).pos(), _pos) < LengthSquare((*objB).pos(), _pos);
		});

		// 移動
		if ((*_input).LStickState().first.isInput)
		{
			_rad = RAD(static_cast<double>((*_input).LStickState().first.angle));
			_pos += {_speed * cos(_rad), _speed * sin(_rad)};

			dir((*_input).LStickState().first.dir);
		}

		// ミニマップの表示切替
		if ((*_input).btnState(INPUT_ID::BTN_START).first && !(*_input).btnState(INPUT_ID::BTN_START).second)
		{
			lpMap.miniMapDrawFlag();
		}

		// テスト用のカメラ特殊移動
		if ((*_input).btnState(INPUT_ID::BTN_RS).first && !(*_input).btnState(INPUT_ID::BTN_RS).second)
		{
			lpCamera.SetMoveData({ 1280.0,390.0 });
			lpCamera.exMoveFlag(true);
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

	// targetが設定されているときはそいつを光らせる
	if (!_tageObj.expired())
	{
		(*_tageObj.lock()).glowFlag(true);
	}
	lpMap.ChangeChip(_pos, _rad, 1);
	/*TRACE("%lf\n", _pos.x);
	TRACE("%lf\n", _pos.y);*/
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

bool Player::throwPot(void)
{
	return _throwPot;
}


Player::~Player()
{
}

void Player::Init(void)
{
	// ----------アニメーション登録開始
	AnimVector data;

	ImageKey key = { static_cast<IMG>(_plNum),STATE::NORMAL };

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

	key.second = STATE::DEATH;

	data.emplace_back(IMAGE_ID(key)[0], 10);
	data.emplace_back(IMAGE_ID(key)[0], 10);

	SetAnim({ STATE::DEATH,DIR::DOWN }, data);
	
	_unitID = UNIT_ID::PLAYER;
	_team = TEAM_TAG::ALLY_TEAM;
	_searchRange = 40.0;
	_weight = 10;
	_holdWeightMax = 5;
	_throwRange = 300.0;
	_serialNum = lpSceneMng.serialNumCnt();
	lpSceneMng.AddSerialNum();
	_playerHPImg[0] = lpImageMng.GetID({ IMG::PL_HP_R,STATE::NORMAL }, "image/playerHP_R.png")[0];
	_playerHPImg[1] = lpImageMng.GetID({ IMG::PL_HP_G,STATE::NORMAL }, "image/playerHP_G.png")[0];
	_heartImg = lpImageMng.GetID({ IMG::HEART,STATE::NORMAL }, "image/heart.png")[0];
	_hpID = MakeScreen(240, 24, true);

	_speed = 5.0;
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);

	_funcState = { {STATE::NORMAL,PlayerNormal()},{STATE::HOLD,PlayerHold()},{STATE::THROW,PlayerThrow()} ,{STATE::DEATH,PlayerDeath()} };

	_hp = 20;
	_hpMax = 20;


	// 初期アニメーション
	state(STATE::NORMAL);
	dir(DIR::DOWN);
}

void Player::DrawHP(void)
{
	// 操作対象のプレイヤーだったらUIに表示、ほかのプレイヤーだったらObjのDrawを呼び出すようにする
	// 今はネットワークつないでないので呼び出さない
	SetDrawScreen(_hpID);
	DrawRectGraph(240 * _hp / _hpMax, 0, 240 * _hp / _hpMax, 0,240 - (240 * _hp / _hpMax), 24, _playerHPImg[0], true, false);
	DrawRectGraph(0, 0, 0, 0, 240 * _hp / _hpMax, 24, _playerHPImg[1], true, false);
	SetDrawScreen(DX_SCREEN_BACK);

	lpSceneMng.AddDrawQue({ _hpID,
		130.0,
		15.0,
		0.0,
		1.0,
		_zOrder + 1,
		LAYER::UI ,
		DX_BLENDMODE_NOBLEND,
		255 });

	lpSceneMng.AddDrawQue({ _heartImg,
		20,
		15.0,
		0.0,
		1.0,
		_zOrder + 1,
		LAYER::UI ,
		DX_BLENDMODE_NOBLEND,
		255 });
}

void Player::throwPot(bool throwMode)
{
	_throwPot = throwMode;
}
