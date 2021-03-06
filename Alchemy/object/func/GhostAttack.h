#pragma once
#include <vector>
#include <object\Obj.h>
#include <Vector2.h>

enum class MOVE_TYPE
{
	CHARGE,		// ﾁｬｰｼﾞ
	SHOT,		// 撃つ
	BLAST		// 爆発
};

#define MAX_CNT 60.0		// 最大ｶｳﾝﾄと弾のｽﾋﾟｰﾄﾞ

struct GhostAttack
{
public:
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);

private:
	// 各ｴﾌｪｸﾄの動き
	void Charge(Obj& obj);								// ﾁｬｰｼﾞ
	void Shot(Obj& obj);								// 発射
	void Blast(Obj& obj);								// 爆発

	bool IsHitObj(Vector2Dbl shot, Vector2Dbl targetPos,Vector2Int targetSize);	// 距離で測る

	MOVE_TYPE _move = MOVE_TYPE::CHARGE;				// 場所がないから初期化する
	double _endCnt;										// 弾が一定ｶｳﾝﾄ当たらなかったら消えて切り替える
	Vector2Dbl _shotPos;								// 弾の座標
	Vector2Dbl _shotSpeed;								// 弾のｽﾋﾟｰﾄﾞ 
};

