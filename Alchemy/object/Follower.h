#pragma once
#include <functional>
#include "Obj.h"
#include "FOLLOWER_TYPE.h"
								// éÌï 			ç¿ïW		í Çµî‘çÜ
using FollowerState = std::tuple<FOLLOWER_TYPE, Vector2Dbl, int>;

class Follower :
	public Obj
{
public:
	Follower();
	Follower(FollowerState followerState, sharedObj potObj);
	~Follower();
	void Update(std::vector<sharedObj>& objList) override;
	int getType(void)override;
private:
	void Init();
	FOLLOWER_TYPE _followerType;
	static std::map<FOLLOWER_TYPE, std::function<bool(Obj&)>> followerInitMap;
};

