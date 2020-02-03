#pragma once
#include <vector>
#include "../object/Obj.h"
#include "InputState.h"
#include "../object/PlNum.h"
#include "../NetWork/NetWork.h"

class NetState :
	public InputState
{
public:
	NetState(PlNum plNum/*, Obj& obj*/);
	~NetState();
	void Update(std::vector<sharedObj>& objList)override;
private:
	void SearchObj(std::vector<sharedObj>& List);
	bool _searchFlag;
	std::vector<MES> _keyBuf;
	unsigned int _num;
	int _missingCnt;
	PlNum _plNum;
	std::weak_ptr<Obj> _plObj;
};

