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
	_syncTime = SYNC_TIME;
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
	_syncTime--;
}

MES NetWork::GetMes(PlNum num, MES_TYPE type)
{
	return (*NetWork::_netWorkUnit).GetMes(num, type);
}

void NetWork::GetKey(std::vector<MES>& buf, PlNum num)
{
	(*NetWork::_netWorkUnit).GetKey(buf, num);
}

void NetWork::ReSetRecMes(void)
{
	(*NetWork::_netWorkUnit).ReSetRecMes();
}

void NetWork::SyncObj(Player & obj)
{
	if (!(*NetWork::_netWorkUnit).CheckSyncMes(obj._plNum))
	{
		return;
	}
	auto tmpMes = (*NetWork::_netWorkUnit).GetMes(obj._plNum, MES_TYPE::SYNC);
	if (static_cast<MES_TYPE>(tmpMes.check.type) != MES_TYPE::SYNC)
	{
		return;
	}
	obj._pos.x = static_cast<double>(tmpMes.sync.x);
	obj._pos.y = static_cast<double>(tmpMes.sync.y);
}

MES NetWork::GetMes(MES_TYPE type)
{
	return (*NetWork::_netWorkUnit).GetMes(type);
}

PlNum NetWork::GetPlNum(void)
{
	return (*NetWork::_netWorkUnit).GetPlNum();
}



void NetWork::MakeKeyMes(KeyMap  butan, StickState & stick)
{
	if (!(*NetWork::_netWorkUnit).LinkFlag())
	{
		return;
	}
	// ﾒｯｾｰｼﾞ作成
	_tmpMes.key.type = static_cast<unsigned char>(MES_TYPE::KEY);
	_tmpMes.key.num = _keyNum;
	_tmpMes.key.plNum = static_cast<unsigned char>((*NetWork::_netWorkUnit).GetPlNum());
	_tmpMes.key.lf = static_cast<unsigned char>(stick.isInput);
	_tmpMes.key.a = static_cast<unsigned char>(butan.at(INPUT_ID::BTN_A).first);
	_tmpMes.key.b = static_cast<unsigned char>(butan.at(INPUT_ID::BTN_B).first);
	_tmpMes.key.y = static_cast<unsigned char>(butan.at(INPUT_ID::BTN_Y).first);
	_tmpMes.key.lb = static_cast<unsigned char>(butan.at(INPUT_ID::BTN_LB).first);
	_tmpMes.key.rb = static_cast<unsigned char>(butan.at(INPUT_ID::BTN_RB).first);
	_tmpMes.key.ls = stick.angle;
	(*NetWork::_netWorkUnit).AddSendMesList(_tmpMes);
	_keyNum++;
}

void NetWork::MakeSyncMes(Vector2Dbl pos)
{
	if (!(*NetWork::_netWorkUnit).LinkFlag() || _syncTime != 0)
	{
		return;
	}
	// ﾒｯｾｰｼﾞ作成
	_tmpMes.sync.type = static_cast<unsigned char>(MES_TYPE::SYNC);
	_tmpMes.sync.plnum = static_cast<unsigned char>((*NetWork::_netWorkUnit).GetPlNum());
	_tmpMes.sync.x = static_cast<unsigned int>(pos.x);
	_tmpMes.sync.y = static_cast<unsigned int>(pos.y);
	(*NetWork::_netWorkUnit).AddSendMesList(_tmpMes);
	_syncTime = SYNC_TIME;
}


