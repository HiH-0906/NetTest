#include "FollowerPot.h"
#include "../AI/AimTarget.h"
#include "../AI/TargetDec.h"
#include "../AI/AttackTarget.h"
#include "../AI/wait.h"

FollowerPot::FollowerPot(Obj & obj) : _masterObj(obj)
{
	_aiCtl.AIList(AttackTarget());
	_aiCtl.AIList(AimTarget());
	_aiCtl.AIList(TargetDec());
	_aiCtl.AIList(wait());
}

FollowerPot::~FollowerPot()
{
}

void FollowerPot::Update(std::vector<sharedObj>& objList)
{
	_aiCtl.Update(objList);
}
