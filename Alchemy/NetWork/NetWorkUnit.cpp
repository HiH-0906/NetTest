#include "NetWorkUnit.h"


NetWorkUnit::NetWorkUnit()
{
	_linkFlag = false;
}

NetWorkUnit::~NetWorkUnit()
{
}

bool NetWorkUnit::LinkFlag(bool flag)
{
	_linkFlag = flag;
	return true;
}

const bool NetWorkUnit::LinkFlag(void) const
{
	return _linkFlag;
}


bool NetWorkUnit::SetnetWorkHandle(int handle)
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
	_sendMesList.emplace_back(mes.data);
	return true;
}

bool NetWorkUnit::AddRecMesList(MES mes)
{
	_recMesList.emplace_back(mes);
	return true;
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
		if (static_cast<MES_TYPE>(data.key.type) != type)
		{
			continue;
		}
		if (static_cast<PlNum>(data.key.plNum) == num)
		{
			return data;
		}
	}
	return nonMes;
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

bool NetWorkUnit::GetData(void)
{
	while (CheckData(_plNum))
	{
		AddRecMesList(_mes);
	}
	return true;
}

bool NetWorkUnit::DataSend(int handle, int mes)
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


