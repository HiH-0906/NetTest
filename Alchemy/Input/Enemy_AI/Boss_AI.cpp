#include "Boss_AI.h"
#include "../AI/AimTarget.h"
#include "../AI/TargetDec.h"
#include "../AI/AttackTarget.h"
#include "../AI/wait.h"
#include "../AI/HeadPot.h"

Boss_AI::Boss_AI(Obj & obj) : _masterObj(obj)
{
	_aiCtl.AIList(AttackTarget());
	_aiCtl.AIList(AimTarget());
	_aiCtl.AIList(TargetDec());
	_aiCtl.AIList(HeadPot());
	_aiCtl.AIList(wait());
}

Boss_AI::~Boss_AI()
{
}

void Boss_AI::Update(std::vector<sharedObj>& objList)
{
	_aiCtl.Update(objList);
}
