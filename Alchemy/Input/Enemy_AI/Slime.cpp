#include "Slime.h"
#include "../AI/AimTarget.h"
#include "../AI/TargetDec.h"
#include "../AI/AttackTarget.h"
#include "../AI/wait.h"
#include "../AI/HeadPot.h"

Slime::Slime(Obj & obj) : _masterObj(obj)
{
	_aiCtl.AIList(AttackTarget());
	_aiCtl.AIList(AimTarget());
	_aiCtl.AIList(TargetDec());
	_aiCtl.AIList(HeadPot());
	_aiCtl.AIList(wait());
}

Slime::~Slime()
{
}

void Slime::Update(std::vector<sharedObj>& objList)
{
	_aiCtl.Update(objList);
}
