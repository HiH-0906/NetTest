#include "FollowMushroom.h"
#include "../AI/AimTarget.h"
#include "../AI/TargetDec.h"
#include "../AI/AttackTarget.h"
#include "../AI/wait.h"
#include "../AI/HealTagDec.h"

FollowMushroom::FollowMushroom(Obj& obj) : _masterObj(obj)
{
	_aiCtl.AIList(AttackTarget());
	_aiCtl.AIList(AimTarget());
	_aiCtl.AIList(HealTagDec());
	_aiCtl.AIList(TargetDec());
	_aiCtl.AIList(wait());
}


FollowMushroom::~FollowMushroom()
{
}

void FollowMushroom::Update(std::vector<sharedObj>& objList)
{
	_aiCtl.Update(objList);
}
