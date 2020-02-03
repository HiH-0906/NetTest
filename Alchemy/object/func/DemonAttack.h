#pragma once
#include <vector>
#include <object\Obj.h>



enum class MOVE_TYPE
{
	CHARGE,
	BLAST
};

struct DemonAttack
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
private:
	// Še´Ìª¸Ä‚Ì“®‚«
	void Charge(Obj& obj);									// Á¬°¼Ş
	void Warning(Obj& obj);									// Œx´Ìª¸Ä
	void Blast(Obj& obj, std::vector<sharedObj>& objList);	// ”š”­

	MOVE_TYPE _move = MOVE_TYPE::CHARGE;					// êŠ‚ª‚È‚¢‚©‚ç‚±‚±‚Å‰Šú‰»‚·‚é
	int _chargeCnt = 0;										// Á¬°¼Ş¶³İÄ
};

