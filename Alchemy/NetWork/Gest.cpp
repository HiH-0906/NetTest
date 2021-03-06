#include "Gest.h"


Guest::Guest(IPDATA IP,int port)
{
	_port = port;
	_plNum = PlNum::PL_NON;
	_ip[_plNum] = IP;
}


Guest::~Guest()
{
	CloseNetWork(netWorkHandle(_plNum));
}

IPDATA Guest::ip(PlNum num)
{
	try
	{
		return _ip.at(PlNum::PL_NON);
	}
	catch (...)
	{
		AST();
		return IPDATA{ 0,0,0,0 };
	}
}

int Guest::netWorkHandle(PlNum num)
{
	try
	{
		return _netWorkHandle.at(PlNum::PL_NON);
	}
	catch (...)
	{
		return 0;
	}
}
void Guest::Connect(void)
{
	// handleがすでにあるか
	if (netWorkHandle(PlNum::PL_NON) == 0)
	{
		// trueで帰ってきたら接続完了
		if (!SetNetWorkHandle(ConnectNetWork(ip(_plNum), _port)))
		{
			return;
		}
		return;
	}
	// MesSize分ﾃﾞｰﾀがﾊﾞｯﾌｧに溜っているかﾁｪｯｸ
	GetData();
	_mes = GetMes(MES_TYPE::CONNECT);
	if (static_cast<MES_TYPE>(_mes.check.type) != MES_TYPE::NON)
	{
		_plNum = static_cast <PlNum>(_mes.key.plNum);
		TRACE("あなたはplayer[%d]です\n", (static_cast<int>(_plNum) + 1));
	}
	if (static_cast<MES_TYPE>(GetMes(_plNum, MES_TYPE::GAMEMODE).check.type) != MES_TYPE::NON)
	{
		_linkFlag = true;
	}
}

bool Guest::GetData(void)
{
	while (CheckData(PlNum::PL_NON))
	{
		AddRecMesList(_mes);
	}
	return true;
}
PlNum Guest::GetPlNum(void)
{
	return _plNum;
}
void Guest::Update(void)
{
	RunMesList();
	GetData();
}
