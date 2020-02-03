#include <Dxlib.h>
#include <_DebugConOut.h>
#include <EffectMng.h>
#include <Camera.h>
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

Boss::Boss(sharedObj potObj)
{
	_potObj = potObj;
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

	if (lpCamera.exMoveFlag())
	{
		if (AddBossMove())
		{
			if (!_addFlag)
			{
				lpCamera.SetMoveData({ lpCamera.exMovePos().x ,lpCamera.exMovePos().y });
				_addFlag = true;
				return;
			}

			if (lpCamera.MoveData())
			{
				lpCamera.exMoveFlag(false);
			}
		}
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
	_pos = { lpSceneMng.WorldSize.x / 2.0,lpSceneMng.WorldSize.y / 4.0 };

	_hpMax = 100;
	_hp = _hpMax;

	_team = TEAM_TAG::ENEMY_TEAM;
	_unitID = UNIT_ID::BOSS;

	_coolCntMax = 100;
	_coolCnt = _coolCntMax;

	_input = std::make_unique<Boss_AI>(*this);
	_extRate = 3.0;
	_size = Vector2Int{ 94,100 }*static_cast<int>(_extRate);

	_weight = INT_MAX;
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);
	_effectScreen = MakeScreen(static_cast<int>(lpEffectMng._screenSize.x), static_cast<int>(lpEffectMng._screenSize.y), true);

	//_bossHPImg[0] = lpImageMng.GetID({ IMG::PL_HP_R,STATE::NORMAL }, "image/playerHP_Back.png")[0];
	_bossHPImg[1] = lpImageMng.GetID({ IMG::BOSS_HP_G,STATE::NORMAL }, "image/bossHP_Frame.png")[0];
	_bossHPImg[2] = lpImageMng.GetID({ IMG::BOSS_HP_G,STATE::HOLD }, "image/bossHP_Gauge.png")[0];

	_funcState = { {STATE::NORMAL, TestEnemyUpdate()}, {STATE::ATTACK, BossAttack()} };

	_hpID = MakeScreen(284, 86, true);
	// 出現時必要なもの
	//_endPos = { 0, _pos.y + 300 };

	_height = 5000.0;
	_addVec = (_height) / BOSS_CNT_MAX;
	_addCnt = 0;
	_addFlag = false;

	// 初期アニメーション
	state(STATE::NORMAL);
	dir(DIR::DOWN);
}

bool Boss::AddBossMove()
{
	_height -= _addVec;

	if (_addCnt >= BOSS_CNT_MAX)
	{
		_height = 0;
		return true;
	}

	_addCnt++;
	return false;
}

void Boss::DrawHP(void)
{
	// 操作対象のプレイヤーだったらUIに表示、ほかのプレイヤーだったらObjのDrawを呼び出すようにする
		// 今はネットワークつないでないので呼び出さない
	SetDrawScreen(_hpID);
	DrawGraph(0, 0, _bossHPImg[0], true);
	//DrawGraph(8, 8, _playerIcon[static_cast<int>(_plNum)][0], true);
	DrawRectGraph(92, 8, 0, 0, 284 * _hp / _hpMax, 40, _bossHPImg[2], true, false);
	DrawGraph(0, 0, _bossHPImg[1], true);

	SetDrawScreen(DX_SCREEN_BACK);

	lpSceneMng.AddDrawQue({ _hpID,
		600.0,
		43.0,
		0.0,
		1.0,
		0.0,
		_zOrder + 1,
		LAYER::UI ,
		DX_BLENDMODE_NOBLEND,
		255 });
}
