#include "enemyAI.h"
#include "object/Obj.h"
#include "AttackTarget.h"
#include "TargetDec.h"
#include "AimTarget.h"
#include "wait.h"
#include "HeadPot.h"

enemyAI::enemyAI(Obj& obj) : _masterObj(obj)
{
	_aiCtl.AIList(AttackTarget());
	_aiCtl.AIList(AimTarget());
	_aiCtl.AIList(TargetDec());
	_aiCtl.AIList(HeadPot());
	_aiCtl.AIList(wait());
}

enemyAI::~enemyAI()
{
}

void enemyAI::Update(std::vector<sharedObj>& objList)
{
	_aiCtl.Update(objList);
}
