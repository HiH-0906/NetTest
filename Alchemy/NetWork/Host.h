#pragma once
#include "NetWork.h"
class Host :
	public NetWorkUnit
{
public:
	Host(int port);
	~Host();
	void ReSetKeyBuf(void)override;
	bool GetData(void)override;
	int netWorkHandle(PlNum num);
	void Connect(void);
	IPDATA ip(PlNum num);
	PlNum GetPlNum(void);						// Œ»İ’ÊM‚µ‚Ä‚¢‚éplayer‚Ìnum
	void RunMesList(void)override;				// Ò¯¾°¼Ş‘—M
	void StartGame(void);						// ¹Ş°Ñ½À°ÄMESì¬
private:
	void TransferMes(void);					// Ò¯¾°¼Ş‚Ì“]‘—
	bool CheckDisConnect(void);					// Ø’f‚µ‚½‚â‚Â‚ª‚¢‚é‚©
	void ConnectCheck(void);					// IP±ÄŞÚ½æ“¾‹y‚ÑÚ‘±Š®—¹Ò¯¾‘—M
	void Update(void);
};

