#include <DxLib.h>
#include "Pot.h"
#include <_DebugConOut.h>
#include <_DebugDispOut.h>
#include "FOLLOWER_TYPE.h"
#include "ENEMY_TYPE.h"
#include "func/PotNormal.h"
#include "func/PotHold.h"
#include "func/PotThrow.h"
#include "../Map.h"

Pot::Pot()
{
	Init();
}


Pot::~Pot()
{
}

void Pot::Update(std::vector<sharedObj>& objList)
{
	try
	{
		_funcState[state()](*this, objList);
	}
	catch (...)
	{
		AST();
	}

	lpMap.ChangeChip(_pos, _rad, 3);
	
}

void Pot::AddMixList(MixData data)
{
	UNIT_ID id;
	std::tie(id, std::ignore) = data;

	lpSceneMng.AddSoundQue({ lpSoundMng.GetID(SOUND::COMBO)[_comboNum], 255, _pos.x, _pos.y });

	if (id == UNIT_ID::ITEM) 
	{
		_comboNum++;
		// コンボの回数によって加える数を増やしてみる
		/*for (int i = 0; i < _comboNum; i++)
		{
			_mixList.emplace_back(data);
		}*/
	}

	_mixList.emplace_back(data);
	_comboCnt = COMBO_TIME_MAX - 30 * (_comboNum - 1);
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
	SetAnim({ STATE::THROW,DIR::DOWN }, data);

	key = { IMG::POT,STATE::HOLD };;

	data.emplace_back(IMAGE_ID(key)[0], 5);
	data.emplace_back(IMAGE_ID(key)[1], 10);
	data.emplace_back(IMAGE_ID(key)[2], 15);
	data.emplace_back(IMAGE_ID(key)[3], 20);
	data.emplace_back(IMAGE_ID(key)[4], 20);

	SetAnim({ STATE::HOLD,DIR::DOWN }, data);
	_unitID = UNIT_ID::POT;
	_team = TEAM_TAG::ALLY_TEAM;
	_searchRange = 40.0;
	_weight = INT_MAX;
	_pos = lpSceneMng.WorldCenter;
	_size = { 64,84 };
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);
	_speed = 0.0;
	_comboCnt = COMBO_TIME_MAX;
	_hpMax = 200;
	_hp = _hpMax;

	_gaugeImg[0] = lpImageMng.GetID({ IMG::COMBO_GAUGE,STATE::HOLD }, "image/comboGaugeFrame.png")[0];
	_gaugeImg[1] = lpImageMng.GetID({ IMG::COMBO_GAUGE,STATE::NORMAL }, "image/comboGauge.png")[0];
	_gaugeID = MakeScreen(90, 26, true);

	// AddInstanceを通らずにインスタンスされるので通し番号を足しておく
	_serialNum = lpSceneMng.serialNumCnt();
	lpSceneMng.AddSerialNum();

	_funcState = { {STATE::NORMAL,PotNormal()},{STATE::HOLD,PotHold()},{STATE::THROW,PotThrow()} };

	CombiListInit();
	// 初期アニメーション
	dir(DIR::DOWN);
	state(STATE::NORMAL);
}

void Pot::CombiListInit(void)
{
	FILE* filePt;
	fopen_s(&filePt, "data/mixData.csv", "rb");

	if (filePt == nullptr)
	{
		AST();
		return;
	}

	int confType = 0;
	int prob[6] = {0,0,0,0,0,0};
	int probCnt = 0;
	MixCombination combi;

	while (fscanf_s(filePt, "%d, %d, %d, %d, %d, %d, %d", &confType, &prob[0], &prob[1], &prob[2], &prob[3], &prob[4], &prob[5]) != EOF)
	{
		int probCnt = 0;
		probCnt = 0;
		combi.confType = confType;
		for (int i = 0; i < 6; i++)
		{
			while (prob[i])
			{
				combi.mixProb[probCnt] = i;
				probCnt++;
				prob[i]--;
			}
		}
		_combiList.emplace_back(combi);
	}

	fclose(filePt);
}

void Pot::InitFunc(void)
{
}
