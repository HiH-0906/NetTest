#include "Ghost.h"
#include "../AI/AimTarget.h"
#include "../AI/TargetDec.h"
#include "../AI/AttackTarget.h"
#include "../AI/wait.h"
#include "../AI/HeadPot.h"
#include "../AI/RunAway.h"

Ghost::Ghost(Obj & obj) : _masterObj(obj)
{
	//_aiCtl.AIList(RunAway());
	_aiCtl.AIList(AttackTarget());
	_aiCtl.AIList(AimTarget());
	_aiCtl.AIList(TargetDec());
	_aiCtl.AIList(HeadPot());
	_aiCtl.AIList(wait());
}

Ghost::~Ghost()
{
}

void Ghost::Update(std::vector<sharedObj>& objList)
{
	_aiCtl.Update(objList);
}
