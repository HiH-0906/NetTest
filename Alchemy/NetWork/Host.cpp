#include "Host.h"


Host::Host(int port)
{
	_port = port;
	_plNum = PlNum::PL_01;
}


Host::~Host()
{
	if (_netWorkHandle.size())
	{
		for (PlNum num = begin(PlNum()); num < _plNum; ++num)
		{
			CloseNetWork(netWorkHandle(num));
		}
	}
}

void Host::ReSetKeyBuf(void)
{
	if (_keyBuf.size() < 2048)
	{
		return;
	}
	_keyBuf.erase(_keyBuf.begin(), _keyBuf.begin() + 1024);
}

bool Host::GetData(void)
{
	for (PlNum num = begin(PlNum()); num < _plNum; ++num)
	{
		while (CheckData(num))
		{
			AddRecMesList(_mes);
		}
	}
	return true;
}

int Host::netWorkHandle(PlNum num)
{
	try
	{
		return _netWorkHandle.at(num);
	}
	catch (...)
	{
		AST();
		return 0;
	}
}

IPDATA Host::ip(PlNum num)
{
	try
	{
		return _ip.at(num);
	}
	catch (...)
	{
		AST();
		return IPDATA{ 0,0,0,0 };
	}
}

PlNum Host::GetPlNum(void)
{
	return _plNum;
}

void Host::Connect(void)
{
	// 接続待ち状態へ移行
	PreparationListenNetWork(_port);
	// 帰ってきたNetWorkHandleが-1じゃないならtrue
	if (SetNetWorkHandle(GetNewAcceptNetWork()))
	{
		// ipｱﾄﾞﾚｽ獲得&接続したよﾃﾞｰﾀ送信
		ConnectCheck();
		GetData();
		auto checkMes=[&](){
			for (PlNum num = begin(PlNum()); num < GetPlNum(); ++num)
			{
				return static_cast<MES_TYPE>(GetMes(num, MES_TYPE::GAMEMODE).check.type)!=MES_TYPE::NON;
			}
			return false;
		};
		// 4人いる？
		if (_plNum == PlNum::PL_02/*PlNum::PL_MAX*/ || checkMes())
		{
			// 4人接続完了で接続終了
			StartGame();
		}
	}
}


void Host::TransferMes(void)
{
	auto check = [](MES mes) {
		if (static_cast<MES_TYPE>(mes.check.type) == MES_TYPE::KEY)
		{
			return true;
		}
		//else if (static_cast<MES_TYPE>(mes.check.type) == MES_TYPE::SYNC)
		//{
		//	return true;
		//}
		else
		{
			return false;
		}
	};
	if (_recMesList.size() == 0)
	{
		return;
	}
	for (auto data:_recMesList)
	{
		if (!check(data))
		{
			continue;
		}
		AddSendMesList(data);
		AddKeyBuf(data);
	}
}

bool Host::CheckDisConnect(void)
{
	// 切断したやつがいるか
	int DisCnHandle = GetLostNetWork();
	auto specificPlayer = [&]() {
		for (PlNum num = begin(PlNum()); num < _plNum; ++num)
		{
			if (netWorkHandle(num) == DisCnHandle)
			{
				return num;
			}
		}
		return PlNum::PL_NON;
	};
	if (DisCnHandle == -1)
	{
		return false;
	}
	TRACE("player[%d]さんがログアウトしました\n",(static_cast<int>(specificPlayer())+1));
	return true;
}

void Host::ConnectCheck(void)
{
	CONNECT_INF tmpInf = {
		static_cast<unsigned char>(MES_TYPE::CONNECT),
		static_cast<unsigned char>(_plNum)
	};
	// 何番目のPlかﾒｯｾｰｼﾞ作成
	MES tmpMes;
	tmpMes.connect = tmpInf;
	// 切断してしまった時用のIPｱﾄﾞﾚｽ確保
	GetNetWorkIP(netWorkHandle(_plNum), &_ip[_plNum]);
	// 接続確認したよﾒｯｾ送信
	DataSend(netWorkHandle(_plNum), tmpMes);
	TRACE("player[%d]さんが接続しました\n", (static_cast<int>(_plNum) + 1));
	++_plNum;
	TRACE("%d\n", static_cast<int>(_plNum));
}

void Host::RunMesList(void)
{
	if (_sendMesList.size() == 0)
	{
		return;
	}
	// 各Handleに送信
	for (PlNum num = begin(PlNum()); num < _plNum; ++num)
	{
		for (unsigned int i = 0; i < _sendMesList.size(); i++)
		{
			DataSend(netWorkHandle(num), _sendMesList[i]);
		}
	}
	_sendMesList.clear();
}

void Host::StartGame(void)
{
	// 新しい接続を終了
	StopListenNetWork();
	TYPE_INF tmpInf = {
		static_cast<unsigned char>(MES_TYPE::GAMEMODE),
	};
	// ｹﾞｰﾑｽﾀｰﾄﾒｯｾｰｼﾞ作成
	MES tmpMes;
	tmpMes.check = tmpInf;
	AddSendMesList(tmpMes);
	_linkFlag = true;
}

void Host::Update(void)
{
	// 切断ﾁｪｯｸ
	CheckDisConnect();
	RunMesList();
	GetData();
	TransferMes();
}
