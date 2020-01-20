#include "TitleScene.h"
#include "SceneMng.h"
#include <_DebugConOut.h>
#include <Input/PadState.h>
#include<Input/InputState.h>
#include<Input/INPUT_ID.h>
#include"GameScene.h"
#include"EntryScene.h"
#include<common\ImageMng.h>

TitleScene::TitleScene()
{
	TRACE("ﾀｲﾄﾙｼｰﾝ\n");
	_padnum = GetJoypadNum();
	TRACE("接続PAD数は%dです\n", _padnum);
	_selectnum = 0;
	_selectFlag = false;
	startFlag = false;
	endFlag = false;
	_cursorPos.x = 0.0;
	_cursorPos.y = 0.0;
	DrawInit();
	Init();
}


TitleScene::~TitleScene()
{
}

UniqueBase TitleScene::Update(UniqueBase own)
{
	if (!endFlag)
	{
		(*_input[0]).Update(_objList);

		if (((*_input[0]).btnState(INPUT_ID::BTN_START).first) && (!_selectFlag))
		{
			_selectFlag = true;
			_selectnum = 1;
			TRACE("タイトルセレクト開始\n");
		}
	}
	if (_selectFlag)
	{
		TitleSelect();
		lpSceneMng.AddDrawQue({ _cursor,_cursorPos.x,_cursorPos.y,0,0,LAYER::CHAR,DX_BLENDMODE_NOBLEND,255 });
		lpSceneMng.AddDrawQue({ _selectTex,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y+200,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
	}
	else
	{
		if ((!startFlag)&&(!endFlag))
		{
			lpSceneMng.AddDrawQue({ _titleTex,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y + 200,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
		}
	}
	if (startFlag)
	{
		return std::make_unique<GameScene>();
		//return std::make_unique<EntryScene>();
	}
	if (endFlag)
	{
		TRACE("ゲーム終了\n");
		lpSceneMng.AddDrawQue({ _endBG,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y,0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });

	}
	else
	{
		lpSceneMng.AddDrawQue({ _titleBG,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y,0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });
	}
	return std::move(own);
}

void TitleScene::Init(void)
{
	_input[0] = std::make_unique<PadState>(DX_INPUT_PAD1);
}

void TitleScene::TitleSelect(void)
{

	_cursorPos.x = 350;
	(*_input[0]).Update(_objList);
	if (((*_input[0]).LStickState().first.isInput))
	{
		if ((*_input[0]).LStickState().first.dir == DIR::DOWN)
		{
			if (_selectnum < 2)
			{
				_selectnum += 1;
			}
			else
			{
				_selectnum = 2;
			}
		}
		else if ((*_input[0]).LStickState().first.dir == DIR::UP)
		{
			if (_selectnum > 1)
			{
				_selectnum -= 1;
			}
			else
			{
				_selectnum = 1;
			}
		}
	}
	else
	{
		DIR::LEFT;
	}
	if (_selectnum == 1)
	{
		_cursorPos.y = lpSceneMng.ScreenCenter.y + 150.0;
	}
	if (_selectnum == 2)
	{
		_cursorPos.y = lpSceneMng.ScreenCenter.y + 275.0;
	}
	TRACE("今の選択肢は%d番目です\n", _selectnum);
	if (((*_input[0]).btnState(INPUT_ID::BTN_A).first))
	{
		if (_selectnum == 1)
		{
			startFlag = true;
		}
		if (_selectnum == 2)
		{
			endFlag = true;
		}
		_selectFlag = false;
		_selectnum = 0;
		TRACE("タイトルセレクト終了\n");
	}
	if (((*_input[0]).btnState(INPUT_ID::BTN_B).first))
	{
		_selectFlag = false;
		_selectnum = 0;
		TRACE("タイトルセレクト終了\n");
	}
}

void TitleScene::DrawInit(void)
{
	//ImageMng::GetInstance().GetID( "TitleBG", "image/TitleBG.png");
	_titleBG = LoadGraph("image/TitleBG.png");
	_endBG = LoadGraph("image/END.png");
	_cursor = LoadGraph("image/cursor.png");
	_selectTex = LoadGraph("image/TitleSelect.png");
	_titleTex = LoadGraph("image/start_button.png");

}
