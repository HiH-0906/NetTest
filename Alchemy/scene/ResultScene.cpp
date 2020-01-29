#include "ResultScene.h"
#include"TitleScene.h"
#include "SceneMng.h"
#include <_DebugConOut.h>
#include <Input/PadState.h>
#include<Input/InputState.h>
#include<Input/INPUT_ID.h>



ResultScene::ResultScene()
{
	TRACE("Ø»ÞÙÄ¼°Ý\n");
	_cnt = 0;
	DrawInit();
	Init();
}


ResultScene::~ResultScene()
{
}

UniqueBase ResultScene::Update(UniqueBase own)
{
	(*_input).Update(_objList);

	if ((*_input).btnState(INPUT_ID::BTN_A).first)
	{
		SetDrawBright(255, 255, 255);
		return std::make_unique<TitleScene>();
	}



	SetDrawBright(_cnt, _cnt, _cnt);
	//lpSceneMng.AddDrawQue({ _resultBG,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y,0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });
	lpSceneMng.AddDrawQue({ _resultLogo,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y-50.0,0.0,1.0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });
	if (_cnt >= 300)
	{
		lpSceneMng.AddDrawQue({ _resultTex,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenSize.y - 100,0.0,1.0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
	}

	_cnt += 2;

	return std::move(own);
}

void ResultScene::Init(void)
{
	_input = std::make_unique<PadState>(DX_INPUT_PAD1);
}

void ResultScene::DrawInit(void)
{
	//_resultBG = LoadGraph("image/ResultBG.png");
	_resultLogo = LoadGraph("image/ResultLogo.png");
	_resultTex = LoadGraph("image/end_button.png");
}
