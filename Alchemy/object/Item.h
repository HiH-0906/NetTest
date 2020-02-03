#pragma once
#include "object/Obj.h"
#include "FOLLOWER_TYPE.h"
class Item :
	public Obj
{
public:
	Item(int type, Vector2Dbl pos);
	~Item();
	void Update(std::vector<sharedObj>& objList)override;
	int getType(void)override;
	int floatCnt(void);
private:
	FOLLOWER_TYPE _type;
	void Init(void);
	int _floatCnt;
};

