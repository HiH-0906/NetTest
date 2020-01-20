#pragma once
#include <functional>
#include "Obj.h"
#include <Vector2.h>
#include <scene\BaseScene.h>
#include "ENEMY_TYPE.h"
#include <ImageMng.h>

							// í—Ş			À•W	  // ’Ê‚µ”Ô†	
using EnemyState = std::tuple<ENEMY_TYPE, Vector2Dbl, int>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState enemyState, sharedObj potObj);
	void Update(std::vector<sharedObj>& objList) override;
	const ENEMY_TYPE enemyType(void)const;
	int getType(void)override;
	~Enemy();
private:
	void Init(void);

	// À²Ìß‚²‚Æ‚ÉInit‚ğŒÄ‚Ô
	static std::map<ENEMY_TYPE, std::function<bool(Obj&)>> enemyInitMap;

	ENEMY_TYPE _enemyType;
};

