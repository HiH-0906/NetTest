#include "UI_Mng.h"

std::unique_ptr<UI_Mng, UI_Mng::UI_MngDeleter> UI_Mng::_sInstance;

void UI_Mng::AddMessage(Text mes)
{
	_mesBoard.AddMesList(mes);
}

UI_Mng::UI_Mng()
{
}


UI_Mng::~UI_Mng()
{
}
