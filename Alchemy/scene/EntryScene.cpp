#include "EntryScene.h"
#include "SceneMng.h"
#include <_DebugConOut.h>
#include <Input/PadState.h>
#include<Input/InputState.h>
#include<Input/INPUT_ID.h>
#include"GameScene.h"
#include<object/PlNum.h>

EntryScene::EntryScene()
{
	_padnum = GetJoypadNum();
	_entryPadnum = 0;
	_fadespeed = 15;
	_fadecolor = 0;
	for (int i = 0; i < _padnum; i++)
	{
		_entrnum[i] = 0;
		_cnt[i] = 0;
	}
	DrawInit();
	Init();

	func = { &EntryScene::EntryStart };

}


EntryScene::~EntryScene()
{
}

UniqueBase EntryScene::Update(UniqueBase own)
{
	SetDrawBright(_fadecolor, _fadecolor, _fadecolor);

	for (int i = 0; i < _padnum; i++)
	{
		(*_input[i]).Update(_objList);
		if (((*_input[i]).btnState(INPUT_ID::BTN_A).first) && (_entrnum[i] == 1))
		{
			return std::make_unique<GameScene>();
		}
		
	}

	for (int j = 0; j < 4; j++)
	{
		lpSceneMng.AddDrawQue({ _backImage[j],(320.0 * static_cast<double>((j + 1))) - 160.0,lpSceneMng.ScreenCenter.y,0.0,1.0,0.0,0,LAYER::CHAR,DX_BLENDMODE_NOBLEND,255 });
	}
	lpSceneMng.AddDrawQue({ _skyimage, lpSceneMng.ScreenCenter.x,208.0,0.0,1.0,0.0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });
	lpSceneMng.AddDrawQue({ _entryBG,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y,0.0,1.0,0.0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });

	(this->*func)();

	return std::move(own);
}

void EntryScene::Init(void)
{
	_input[0] = std::make_unique<PadState>(DX_INPUT_PAD1);
	_input[1] = std::make_unique<PadState>(DX_INPUT_PAD2);
	_input[2] = std::make_unique<PadState>(DX_INPUT_PAD3);
	_input[3] = std::make_unique<PadState>(DX_INPUT_PAD4);
}

void EntryScene::DrawInit(void)
{
	_entryBG = LoadGraph("image/TitleBG.png");
	for (int i = 0; i < 4; i++)
	{
		_backImage[i] = LoadGraph("image/Woodback.png");
	}
	LoadDivGraph("image/Player_walk.png", 16, 4, 4, 266, 249, *_entryImage);
	_skyimage = LoadGraph("image/sky.png");
}

void EntryScene::EntryStart(void)
{
	if (_fadecolor < 255)
	{
		_fadecolor += _fadespeed;
	}
	else
	{
		func = &EntryScene::EntryNormal;
	}
}

void EntryScene::EntryNormal(void)
{
	for (int i = 0; i < _padnum; i++)
	{
		(*_input[i]).Update(_objList);

		if (_entrnum[i] != 0)
		{
				lpSceneMng.AddDrawQue({ _entryImage[(_entrnum[i] - 1)][((_cnt[i] / 10) % 4)],(320.0 * static_cast<double>((i + 1))) - 160.0,lpSceneMng.ScreenCenter.y,0,1.2,0.0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
				_cnt[i]++;
		}

		if ((*_input[i]).btnState(INPUT_ID::BTN_START).first)
		{
			auto instancedata = [&]() {
				for (auto listdata : lpSceneMng.playerList())//instancelist‚Ì’†‚ðŒ©‚é
				{
					if (std::get<static_cast<int>(PLAYER_QUE::PADNUM)>(listdata) == i + 1)//‚Ù‚©‚Ì‚à‚Ì‚Æ”í‚Á‚Ä‚È‚¢‚©Œ©‚é
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
			_entryPadnum += 1;
			_entrnum[i] = _entryPadnum;
		}

	}
}
