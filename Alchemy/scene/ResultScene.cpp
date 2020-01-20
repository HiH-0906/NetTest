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
		return std::make_unique<TitleScene>();
	}


	return std::move(own);
}

void ResultScene::Init(void)
{
	_input = std::make_unique<PadState>(DX_INPUT_PAD1);
}
