#include "FollowGhost.h"
#include "../AI/AimTarget.h"
#include "../AI/TargetDec.h"
#include "../AI/AttackTarget.h"
#include "../AI/wait.h"
#include "../AI/HeadPot.h"

FollowGhost::FollowGhost(Obj & obj) : _masterObj(obj)
{
	_aiCtl.AIList(AttackTarget());
	_aiCtl.AIList(AimTarget());
	_aiCtl.AIList(TargetDec());
	_aiCtl.AIList(wait());
}

FollowGhost::~FollowGhost()
{
}

void FollowGhost::Update(std::vector<sharedObj>& objList)
{
	_aiCtl.Update(objList);
}
