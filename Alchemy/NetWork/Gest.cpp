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
	// handle‚ª‚·‚Å‚É‚ ‚é‚©
	if (netWorkHandle(PlNum::PL_NON) == 0)
	{
		// true‚Å‹A‚Á‚Ä‚«‚½‚çÚ‘±Š®—¹
		if (!SetnetWorkHandle(ConnectNetWork(ip(_plNum), _port)))
		{
			return;
		}
		return;
	}
	// MesSize•ªÃŞ°À‚ªÊŞ¯Ì§‚É—­‚Á‚Ä‚¢‚é‚©Áª¯¸
	if (!CheckData(_plNum))
	{
		return;
	}
	if (static_cast<MES_TYPE>(_mes.check.type) == MES_TYPE::CONNECT)
	{
		_plNum = static_cast <PlNum>(_mes.key.plNum);
		TRACE("‚ ‚È‚½‚Íplayer[%d]‚Å‚·\n", (static_cast<int>(_plNum) + 1));
	}
	else if (static_cast<MES_TYPE>(_mes.check.type) == MES_TYPE::GAMEMODE)
	{
		LinkFlag(true);
	}
	else
	{
		AST();
	}
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
