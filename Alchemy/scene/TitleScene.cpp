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
	_padnum = GetJoypadNum();
	_selectnum = SELECTMENU::START;
	_cursorPos.x =  lpSceneMng.ScreenCenter.x - 200.0;
	_cursorPos.y = lpSceneMng.ScreenCenter.y + 115.0;
	T_logoPos.x = lpSceneMng.ScreenCenter.x;
	T_logoPos.y = -65.0;
	_fadecolor = 255;
	for (int s = 0; s < 2; s++)
	{
		_skyPos[s].x = (lpSceneMng.ScreenCenter.x + (s * lpSceneMng.ScreenSize.x));
		_skyPos[s].y = 208.0;
	}
	_fallSpeed = 2.0;
	_fadespeed = 5;
	_cnt = 0;
	DrawInit();
	Init();

	func = { &TitleScene::TitleNormal };
}


TitleScene::~TitleScene()
{
}

UniqueBase TitleScene::Update(UniqueBase own)
{
	(*_input[0]).Update(_objList);

	SetDrawBright(_fadecolor, _fadecolor, _fadecolor);

	if ((func == &TitleScene::NEXT) && (_fadecolor <= 0))
	{
		//return std::make_unique<GameScene>();
		return std::make_unique<EntryScene>();
	}

	lpSceneMng.AddDrawQue({ _titleLogo,lpSceneMng.ScreenCenter.x,T_logoPos.y,0.0,1.0,0.0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
	for (int s = 0; s < 2; s++)
	{
		lpSceneMng.AddDrawQue({ _skyimage[s], _skyPos[s].x,_skyPos[s].y,0.0,1.0,0.0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });
		_skyPos[s].x -= 0.3;
		if ((_skyPos[s].x + lpSceneMng.ScreenCenter.x) <= 0.0)
		{
			_skyPos[s].x = lpSceneMng.ScreenSize.x + lpSceneMng.ScreenCenter.x;
		}
	}
	lpSceneMng.AddDrawQue({ _titleBG,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y,0.0,1.0,0.0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });

	(this->*func)();

	return std::move(own);
}

void TitleScene::Init(void)
{
	_input[0] = std::make_unique<PadState>(DX_INPUT_PAD1);
}

void TitleScene::TitleSelect(void)
{
		
	lpSceneMng.AddDrawQue({ _selectTex,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y + 150.0,0.0,1.0,0.0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });

	lpSceneMng.AddDrawQue({ _cursor,_cursorPos.x,_cursorPos.y,0.0,1.0,0.0,0,LAYER::CHAR,DX_BLENDMODE_NOBLEND,255 });
	
	(*_input[0]).Update(_objList);
	if (((*_input[0]).LStickState().first.isInput))
	{
		if ((*_input[0]).LStickState().first.dir == DIR::DOWN)
		{
			_selectnum = SELECTMENU::END;
		}
		else if ((*_input[0]).LStickState().first.dir == DIR::UP)
		{
			_selectnum = SELECTMENU::START;
		}
	}
	else
	{
		DIR::LEFT;
	}
	if (_selectnum == SELECTMENU::START)
	{
		_cursorPos.y = lpSceneMng.ScreenCenter.y + 115.0;
	}
	if (_selectnum == SELECTMENU::END)
	{
		_cursorPos.y = lpSceneMng.ScreenCenter.y + 185.0;
	}
	if (((*_input[0]).btnState(INPUT_ID::BTN_A).first))
	{
		if (_selectnum == SELECTMENU::END)
		{
			func = &TitleScene::TitleEnd;
		}
		else
		{
			func = &TitleScene::NEXT;
		}
	}
	if (((*_input[0]).btnState(INPUT_ID::BTN_B).first))
	{
		func = &TitleScene::TitleNormal;
		TRACE("タイトルセレクト終了\n");
	}
}
void TitleScene::TitleEnd(void)
{
	func = &TitleScene::TitleNormal;
}

void TitleScene::TitleNormal(void)
{
	if (T_logoPos.y < lpSceneMng.ScreenCenter.y - 100.0)
	{
		T_logoPos.y += _fallSpeed;
	}
	else
	{
		T_logoPos.y = (lpSceneMng.ScreenCenter.y - 100.0);
	}
	if (((*_input[0]).btnState(INPUT_ID::BTN_START).first))
	{
		_cnt = 0;

		T_logoPos.y = (lpSceneMng.ScreenCenter.y - 100.0);
		func = &TitleScene::TitleSelect;
		_selectnum = SELECTMENU::START;
		TRACE("タイトルセレクト開始\n");
	}
	else
	{
		if ((_cnt / 45) % 2 == 0)
		{
			lpSceneMng.AddDrawQue({ _titleTex,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y + 200.0,0.0,1.0,0.0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
		}

		_cnt++;
	}
}

void TitleScene::NEXT(void)
{
	_fadecolor -= _fadespeed;
}

void TitleScene::DrawInit(void)
{
	//ImageMng::GetInstance().GetID( "TitleBG", "image/TitleBG.png");
	_titleBG   = LoadGraph("image/TitleBG.png");
	for (int s = 0; s < 2; s++)
	{
		_skyimage[s] = LoadGraph("image/sky.png");
	}
	_cursor    = LoadGraph("image/selector.png");
	_selectTex = LoadGraph("image/TitleSelect.png");
	_titleTex  = LoadGraph("image/start_button.png");
	_titleLogo = LoadGraph("image/TitleLogo.png");
}
