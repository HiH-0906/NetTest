#include "EntryScene.h"
#include "SceneMng.h"
#include <_DebugConOut.h>
#include <Input/PadState.h>
#include<Input/InputState.h>
#include<Input/INPUT_ID.h>
#include"GameScene.h"
#include"TitleScene.h"
#include<object/PlNum.h>

EntryScene::EntryScene()
{
	TRACE("ｴﾝﾄﾘｰｼｰﾝ\n");
	_padnum = GetJoypadNum();
	_entryPadnum = 0;
	for (int i = 0; i < _padnum; i++)
	{
		_entrnum[i] = 0;
	}
	TRACE("接続PAD数は%dです\n", _padnum);
	Init();
}


EntryScene::~EntryScene()
{
}

UniqueBase EntryScene::Update(UniqueBase own)
{
	for (int i = 0; i < _padnum; i++)
	{
		(*_input[i]).Update(_objList);
		if (((*_input[i]).btnState(INPUT_ID::BTN_A).first) && (_entrnum[i] == 1))
		{
			return std::make_unique<GameScene>();
		}
		//if (static_cast<PlNum>(lpSceneMng.GetPlayerListSize()) >= PlNum::PL_MAX)
		//{
		//	if (((*_input[i]).btnState(INPUT_ID::BTN_A).first))
		//	{
		//		return std::make_unique<GameScene>();
		//	}
		//}
		//else
		//{
			if (((*_input[i]).btnState(INPUT_ID::BTN_B).first))
			{
				//return std::make_unique<TitleScene>();
			}
		//}
		if ((*_input[i]).btnState(INPUT_ID::BTN_START).first)
		{
			auto instancedata = [&]() {
				for (auto listdata : lpSceneMng.playerList())//instancelistの中を見る
				{
					if (std::get<static_cast<int>(PLAYER_QUE::PADNUM)>(listdata) == i + 1)//ほかのものと被ってないか見る
					{
						return true;
					}
				}
				return false;
			};

			if (instancedata())
			{
				continue;
			}
			lpSceneMng.AddPlayerQue({ static_cast<PlNum>(lpSceneMng.GetPlayerListSize()),{lpSceneMng.ScreenSize.x / 2.0 + (100.0*i),lpSceneMng.ScreenSize.y / 4.0}, i + 1 });
			TRACE("プレイヤー%dがPAD%dで参加です\n", _entryPadnum + 1, i + 1);
			_entryPadnum += 1;
			_entrnum[i] = _entryPadnum;
		}

	}


	return std::move(own);
}

void EntryScene::Init(void)
{
	_input[0] = std::make_unique<PadState>(DX_INPUT_PAD1);
	_input[1] = std::make_unique<PadState>(DX_INPUT_PAD2);
	_input[2] = std::make_unique<PadState>(DX_INPUT_PAD3);
	_input[3] = std::make_unique<PadState>(DX_INPUT_PAD4);
}
