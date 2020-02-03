#pragma once
#include "object/Obj.h"
class Boss :
	public Obj
{
public:
	Boss();
	~Boss();
	void Update(std::vector<sharedObj>& objList) override;

private:
	void Init();
};

