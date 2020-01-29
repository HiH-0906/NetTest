#pragma once
#include <functional>
#include "BaseScene.h"
#include <object/Obj.h>
#include <scene/SceneMng.h>
#include "Camera.h"

using funcAct = std::function<bool(ActQueT&, std::vector<sharedObj>&)>;
using enemyData = std::tuple<int, int, double, double>;

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
	void enemyListInit(void);				// 敵の情報をﾘｽﾄに追加
	void searchEnlist(void);
	void RunActQue(std::vector<ActQueT> actList)override;
	void PlayerInstance(std::vector<PlayerQueT> &playerList, sharedObj potObj);
	void RunInstanceQue(std::vector<InstanceQueT> instanceList)override;

	sharedObj potObj;
	std::shared_ptr<Camera> _camera;
	std::map<ACT_QUE, funcAct> funcQue;
	std::vector<enemyData> _enemyList;		// 敵の出現ﾘｽﾄ<出現ﾌﾚｰﾑ, ﾀｲﾌﾟ, 座標X, 座標Y>
};

