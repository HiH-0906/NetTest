#pragma once
#include <functional>
#include "BaseScene.h"
#include <object/Obj.h>
#include <scene/SceneMng.h>
#include "Camera.h"

using funcAct = std::function<bool(ActQueT&, std::vector<sharedObj>&)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	UniqueBase Update(UniqueBase own)override;
private:
	void initFunc(void);
	void initImg(void);
	void initeffect(void);
	void RunActQue(std::vector<ActQueT> actList)override;
	void PlayerInstance(std::vector<PlayerQueT> &playerList, sharedObj potObj);
	void RunInstanceQue(std::vector<InstanceQueT> instanceList)override;

	sharedObj potObj;
	std::shared_ptr<Camera> _camera;
	std::map<ACT_QUE, funcAct> funcQue;
};

