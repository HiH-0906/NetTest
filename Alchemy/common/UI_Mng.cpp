#include <DxLib.h>
#include <scene/SceneMng.h>
#include "UI_Mng.h"

std::unique_ptr<UI_Mng, UI_Mng::UI_MngDeleter> UI_Mng::_sInstance(new UI_Mng());

void UI_Mng::AddMessage(Text mes)
{
	(*_mesBoard).AddMesList(mes);
}

void UI_Mng::AddUIQue(UIQue & que)
{
	_uiList.emplace_back(que);
}

void UI_Mng::Draw(void)
{
	SetDrawScreen(_screen);
	ClsDrawScreen();

	for (auto ui : _uiList)
	{
		double x, y;
		int image;

		std::tie(x, y, image) = ui;

		DrawGraph(static_cast<int>(x), static_cast<int>(y), image, true);
	}

	(*_mesBoard).DrawUpdate();
	DrawGraph(0, 400, (*_mesBoard).mesScreen(), true);

	SetDrawScreen(DX_SCREEN_BACK);
}

void UI_Mng::UI_Init(void)
{
	_screen = MakeScreen(static_cast<int>(lpSceneMng.ScreenSize.x), static_cast<int>(lpSceneMng.ScreenSize.y), true);
	_mesBoard = std::make_unique<Message>();
}

int UI_Mng::screen(void)
{
	return _screen;
}

UI_Mng::UI_Mng()
{
}


UI_Mng::~UI_Mng()
{
}
