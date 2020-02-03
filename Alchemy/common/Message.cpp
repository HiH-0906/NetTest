#include <DxLib.h>
#include "Message.h"



Message::Message()
{
	Text text;
	text.LoadFontImg();
	_mesScreen = MakeScreen(320, 320,true);
	_mesMoveCnt = 0;
	_boardImg = LoadGraph("image/mesBoard.png");
	SetDrawScreen(_mesScreen);
	DrawGraph(0, 0, _boardImg, true);
	SetDrawScreen(DX_SCREEN_BACK);

}


Message::~Message()
{
}

void Message::AddMesList(Text & mes)
{
	_mesList.emplace(_mesList.begin(), mes);
	if (_mesList.size() > 11)
	{
		_mesList.pop_back();
	}
	_mesMoveCnt = 10;
}

int Message::mesScreen(void)
{
	return _mesScreen;
}

void Message::DrawUpdate(void)
{
	SetDrawScreen(_mesScreen);
	ClsDrawScreen();

	DrawGraph(0, 0, _boardImg,true);
	for (int i = 0; i < _mesList.size(); i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 5 * i);
		DrawRotaGraph(_mesList[i].size().x / 2, 320 - 32 * (i + 1 - static_cast<double>(_mesMoveCnt) / 10.0) + 16, 1.0 - (static_cast<double>(_mesMoveCnt) / 10.0 * (i == 0)), 0.0, _mesList[i].screen(), true, false);
		
	}
	if (_mesMoveCnt)
	{
		_mesMoveCnt--;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(DX_SCREEN_BACK);
}
