#include "NetWork.h"
#include "Host.h"
#include "Gest.h"

std::unique_ptr<NetWork, NetWork::NetWorkDeleter> NetWork::sInstans(new NetWork());

bool NetWork::NetMode(NETMODE mode)
{
	_netMode = mode;
	if (_netWorkUnit != nullptr)
	{
		return true;
	}
	switch (_netMode)
	{
	case NETMODE::OFFLINE:
		// ｵﾌﾗｲﾝにはunitいらないのでスルー
		break;
	case NETMODE::HOST:
		_netWorkUnit = std::make_unique<Host>(9850);
		break;
	case NETMODE::GUEST:
		_netWorkUnit = std::make_unique<Guest>(IPDATA{ 172,20,44,53 }, 9850);
		break;
	case NETMODE::MAX:
		AST();
		break;
	default:
		AST();
		break;
	}
	return true;
}

const NETMODE NetWork::NetMode(void)
{
	return _netMode;
}



bool NetWork::Active(void)
{
	if (NetWork::_netWorkUnit == nullptr)
	{
		return false;
	}
	return (*NetWork::_netWorkUnit).LinkFlag();
}


NetWork::NetWork()
{
	_netMode = NETMODE::OFFLINE;
	_matchTime = MATCH_TIME;
	_netWorkUnit = nullptr;
	_keyNum = 0;
}

NetWork::~NetWork()
{
}

void NetWork::Connect(void)
{
	// 接続確立してるか
	if (!Active())
	{
		// NetWorkUnitがｲﾝｽﾀﾝｽされてるか
		if (_netWorkUnit != nullptr)
		{
			// 確立してなかったら確立させに行く
			(*NetWork::_netWorkUnit).Connect();
		}
		return;
	}
}

void NetWork::UpDate(void)
{
	if (!NetWork::Active())
	{
		return;
	}
	(*NetWork::_netWorkUnit).Update();
}

MES NetWork::GetMes(PlNum num, MES_TYPE type)
{
	return (*NetWork::_netWorkUnit).GetMes(num, type);
}

void NetWork::ReSetRecMes(void)
{
	(*NetWork::_netWorkUnit).ReSetRecMes();
}

PlNum NetWork::GetPlNum(void)
{
	return (*NetWork::_netWorkUnit).GetPlNum();
}


void NetWork::MakeKeyMes(KeyMap  butan, StickState & stick)
{
	// ﾒｯｾｰｼﾞ作成
	_tmpMes.key.type = static_cast<unsigned char>(MES_TYPE::KEY);
	_tmpMes.key.num = _keyNum;
	_tmpMes.key.plNum = static_cast<unsigned char>((*NetWork::_netWorkUnit).GetPlNum());
	_tmpMes.key.lf = static_cast<unsigned char>(stick.isInput);
	_tmpMes.key.a = static_cast<unsigned char>(butan.at(INPUT_ID::BTN_A).first);
	_tmpMes.key.b = static_cast<unsigned char>(butan.at(INPUT_ID::BTN_B).first);
	_tmpMes.key.y = static_cast<unsigned char>(butan.at(INPUT_ID::BTN_Y).first);
	_tmpMes.key.ls = stick.angle;
	(*NetWork::_netWorkUnit).AddSendMesList(_tmpMes);
	_keyNum++;
}

void NetWork::MakeMatchMes(Vector2Dbl& pos)
{
	if (_matchTime>=0)
	{
		return;
	}
	_tmpMes.match.type = static_cast<unsigned char>(MES_TYPE::MATCH);
	_tmpMes.match.x = static_cast<unsigned short>(pos.x);
	_tmpMes.match.y = static_cast<unsigned short>(pos.y);
	(*NetWork::_netWorkUnit).AddSendMesList(_tmpMes);
	_matchTime = MATCH_TIME;
}

