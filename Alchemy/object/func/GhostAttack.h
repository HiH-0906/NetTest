#pragma once
#include <vector>
#include <object\Obj.h>
#include <Vector2.h>

enum class MOVE_TYPE
{
	CHARGE,		// Á¬°¼Ş
	SHOT,		// Œ‚‚Â
	BLAST		// ”š”­
};

#define MAX_CNT 60.0		// Å‘å¶³İÄ‚Æ’e‚Ì½Ëß°ÄŞ

struct GhostAttack
{
public:
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);

private:
	// Še´Ìª¸Ä‚Ì“®‚«
	void Charge(Obj& obj);								// Á¬°¼Ş
	void Shot(Obj& obj);								// ”­Ë
	void Blast(Obj& obj);								// ”š”­

	bool IsHitObj(Vector2Dbl shot, Vector2Dbl targetPos,Vector2Int targetSize);	// ‹——£‚Å‘ª‚é

	MOVE_TYPE _move = MOVE_TYPE::CHARGE;				// êŠ‚ª‚È‚¢‚©‚ç‰Šú‰»‚·‚é
	double _endCnt;										// ’e‚ªˆê’è¶³İÄ“–‚½‚ç‚È‚©‚Á‚½‚çÁ‚¦‚ÄØ‚è‘Ö‚¦‚é
	Vector2Dbl _shotPos;								// ’e‚ÌÀ•W
	Vector2Dbl _shotSpeed;								// ’e‚Ì½Ëß°ÄŞ 
};

