#include <algorithm>
#include "NetWorkUnit.h"
#include "../_debug/_DebugConOut.h"


NetWorkUnit::NetWorkUnit()
{
	_linkFlag = false;
}

NetWorkUnit::~NetWorkUnit()
{
}

const bool NetWorkUnit::LinkFlag(void) const
{
	return _linkFlag;
}


bool NetWorkUnit::SetNetWorkHandle(int handle)
{
	if (handle == -1)
	{
		return false;
	}

	if (_netWorkHandle.try_emplace(_plNum, handle).second)
	{
		return true;
	}
	return false;
}

bool NetWorkUnit::AddSendMesList(MES mes)
{
	_sendMesList.emplace_back(mes);
	return true;
}

bool NetWorkUnit::AddRecMesList(MES mes)
{
	_recMesList.emplace_back(mes);
	return true;
}

MES NetWorkUnit::GetKeyBuf(PlNum plNum, unsigned int num)
{
	MES nonMes = { 0 };
	for (auto data : _keyBuf)
	{
		if (static_cast<PlNum>(data.key.plNum) != plNum || data.key.num != num)
		{
			continue;
		}
		return data;
	}
	return nonMes;
}

void NetWorkUnit::ReSetRecMes(void)
{
	_recMesList.clear();
}

MES NetWorkUnit::GetMes(PlNum num, MES_TYPE type)
{
	MES nonMes = { 0 };
	for (auto data : _recMesList)
	{
		if (static_cast<MES_TYPE>(data.check.type) != type)
		{
			continue;
		}
		if (static_cast<PlNum>(data.check.plNum) == num)
		{
			return data;
		}
	}
	return nonMes;
}

MES NetWorkUnit::GetMes(MES_TYPE type)
{
	MES nonMes = { 0 };
	for (auto data : _recMesList)
	{
		if (static_cast<MES_TYPE>(data.check.type) != type)
		{
			continue;
		}
		return data;
	}
	return nonMes;
}

void NetWorkUnit::GetKey(std::vector<MES>& buf, PlNum num)
{
	if (_recMesList.size() == 0)
	{
		return;
	}
	for (auto data:_recMesList)
	{
		if (static_cast<MES_TYPE>(data.check.type) != MES_TYPE::KEY)
		{
			continue;
		}
		else if (static_cast<PlNum>(data.key.plNum)!=num)
		{
			continue;
		}
		else
		{
			buf.emplace_back(data);
		}
	}
	return;
}

void NetWorkUnit::RunMesList(void)
{
	if (_sendMesList.size() == 0)
	{
		return;
	}
	// ëóêM
	for (size_t i = 0; i < _sendMesList.size(); i++)
	{
		DataSend(netWorkHandle(_plNum), _sendMesList[i]);
	}
	_sendMesList.clear();
}

void NetWorkUnit::StartGame(void)
{
	TYPE_INF tmpInf = {
		static_cast<unsigned char>(MES_TYPE::GAMEMODE)
	};
	MES tmpMes;
	tmpMes.check = tmpInf;
	AddSendMesList(tmpMes);
}

void NetWorkUnit::AgainDataSend(void)
{
	auto mes = GetMes(MES_TYPE::AGAIN);
	if (static_cast<MES_TYPE>(mes.check.type) != MES_TYPE::AGAIN)
	{
		return;
	}
	mes = GetKeyBuf(static_cast<PlNum>(mes.again.plNum), mes.again.num);
	if (static_cast<MES_TYPE>(mes.check.type) != MES_TYPE::NON)
	{
		AddSendMesList(mes);
	}
}

bool NetWorkUnit::CheckMes(PlNum num, MES_TYPE type)
{
	if (_recMesList.size() == 0)
	{
		return false;
	}
	for (auto data : _recMesList)
	{
		if (static_cast<MES_TYPE>(data.check.type) != type)
		{
			continue;
		}
		if (static_cast<PlNum>(data.sync.plnum) != num)
		{
			continue;
		}
		return true;
	}
	return false;
}

bool NetWorkUnit::DataSend(int handle, MES mes)
{
	if (NetWorkSend(handle, &mes, MES_SIZE) != -1)
	{
		return true;
	}
	return false;
}

bool NetWorkUnit::CheckData(PlNum plNum)
{
	if (GetNetWorkDataLength(netWorkHandle(plNum)) < MES_SIZE)
	{
		return false;
	}
	// √ﬁ∞¿éÊÇËèoÇµ
	if (NetWorkRecv(netWorkHandle(plNum), &_mes, MES_SIZE) == -1)
	{
		return false;
	}
	return true;
}


