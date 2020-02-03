#pragma once
#include <memory>
#include <Message.h>

#define lpUI_Mng UI_Mng::GetInstance()

class UI_Mng
{
public:
	// ºÝ½Ä×¸À
	static UI_Mng & GetInstance(void)
	{
		return *_sInstance;
	}

	void AddMessage(Text mes);

private:
	struct UI_MngDeleter
	{
		void operator()(UI_Mng* uiMng) const
		{
			delete uiMng;
		}
	};
	UI_Mng();
	~UI_Mng();

	Message _mesBoard;

	static std::unique_ptr<UI_Mng, UI_MngDeleter> _sInstance;

};
