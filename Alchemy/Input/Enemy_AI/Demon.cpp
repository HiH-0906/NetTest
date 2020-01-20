#include "Demon.h"
#include "../AI/AimTarget.h"
#include "../AI/TargetDec.h"
#include "../AI/AttackTarget.h"
#include "../AI/wait.h"
#include "../AI/HeadPot.h"

Demon::Demon(Obj & obj) : _masterObj(obj)
{
	_aiCtl.AIList(AttackTarget());
	_aiCtl.AIList(AimTarget());
	_aiCtl.AIList(TargetDec());
	_aiCtl.AIList(HeadPot());
	_aiCtl.AIList(wait());
}

Demon::~Demon()
{
}

void Demon::Update(std::vector<sharedObj>& objList)
{
	_aiCtl.Update(objList);
}
