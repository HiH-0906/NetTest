#pragma once
#include "object/Obj.h"
#include "ENEMY_TYPE.h"
class Item :
	public Obj
{
public:
	Item(ENEMY_TYPE type, Vector2Dbl pos);
	~Item();
	void Update(std::vector<sharedObj>& objList)override;
	int getType(void)override;
	int floatCnt(void);
private:
	ENEMY_TYPE _type;
	void Init(void);
	int _floatCnt;
};

