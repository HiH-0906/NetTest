#include "BaseScene.h"



BaseScene::BaseScene()
{
	_screenPos = { 0.0,0.0};
}

BaseScene::~BaseScene()
{
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	// Ç±Ç±Ç…ì¸Ç¡ÇΩÇÁè¡Ç∑
	actList.clear();
}

void BaseScene::RunInstanceQue(std::vector<InstanceQueT> instanceList)
{
	// âΩÇ‡ÇµÇ»Ç¢
	instanceList.clear();
}

