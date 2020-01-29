#pragma once
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <Vector2.h>
#include <ImageMng.h>
#include <DIR.h>
#include "UNIT_ID.h"
#include "STATE.h"

/* ----------オブジェクト基底クラス--------- */


// 陣営
enum class TEAM_TAG
{
	NON,
	ALLY_TEAM,		// 味方
	ENEMY_TEAM		// 敵
};

class Obj;
class InputState;
class Camera;
class NetWork;
struct PlayerNormal;
struct PlayerHold;
struct PlayerThrow;
struct PotNormal;
struct PotHold;
struct PotThrow;

struct FuncHold;
struct FuncThrow;
struct FuncIntoPot;
struct ThrownUpdate;
struct HoldenUpdate;
struct TestEnemyUpdate;

struct HeadPot;
struct HealTagDec;
struct LookForEnemy;

struct BatAttack;
struct Heal;
struct Slime_Attack;
struct GhostAttack;
struct DemonAttack;
struct OctpusAttack;
struct BeeAttack;

struct SlimeInit;
struct BatInit;
struct MushroomInit;
struct GhostInit;
struct DemonInit;

struct ItemNormal;

struct OctpusInit;
struct BeeInit;
struct FollowMushInit;
struct FollowGhostInit;
struct FollowDemonInit;

using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;
using AnimKey = std::pair<STATE, DIR>;
using funcObj = std::function<void(Obj&,std::vector<sharedObj>& objList)>;

class Obj
{
public:
	Obj();
	virtual void Update(std::vector<sharedObj>& objList) = 0;
	void Draw(void);		// アニメーションの描画	GameScene以外
	void Draw(int id);		// 好きな画像を指定して描画
	virtual ~Obj();

	// get,set関数 : 変数名の_を外したのが関数名
	STATE state(void)const;							
	bool state(STATE newState);

	DIR dir(void)const;
	bool dir(DIR newDir);
	
	bool alive(void) { return _alive; }
	bool alive(bool alive);
	bool dead(void) { return _dead; }
	bool dead(bool dead);

	const Vector2Dbl& pos(void);
	const Vector2Int& size(void);
	const double& rad(void);
	
	virtual void exFlag(bool isEX);
	virtual int getType(void);
	void glowFlag(bool isGlow);

	const int weight(void);
	const UNIT_ID& unitID(void);
	const TEAM_TAG& teamTag(void);

	std::weak_ptr<Obj>& tageObj(void);
	void SetTageObj(sharedObj obj);

	const double& searchRange(void);
	const double& attackRange(void);

	void DoDamage(int power);		// 攻撃されてHPが減る、引数は攻撃力
	const int& hp(void);
	const int& hpMax(void);

	bool isAnimEnd(void);								// アニメーションが終了しているか
	bool SetAnim(const AnimKey key,AnimVector& data);	// アニメーションのデータを登録
	void LoadStaticImg(void);								// HPバーの読み込み

private:
	friend NetWork;
	friend PlayerNormal;
	friend PlayerHold;
	friend PlayerThrow;
	friend PotNormal;
	friend PotHold;
	friend PotThrow;
	friend FuncHold;
	friend FuncThrow;
	friend FuncIntoPot;
	friend ThrownUpdate;
	friend HoldenUpdate;
	friend TestEnemyUpdate;

	// AI
	friend HeadPot;
	friend HealTagDec;
	friend LookForEnemy;

	// 攻撃
	friend BatAttack;
	friend Heal;
	friend Slime_Attack;
	friend GhostAttack;
	friend DemonAttack;
	friend OctpusAttack;
	friend BeeAttack;

	// Enemyのinit
	friend SlimeInit;
	friend BatInit;
	friend MushroomInit;
	friend GhostInit;
	friend DemonInit;

	// Item
	friend ItemNormal;

	// FollowerのInit
	friend OctpusInit;
	friend BeeInit;
	friend FollowMushInit;
	friend FollowGhostInit;
	friend FollowDemonInit;

	std::map<AnimKey, AnimVector> _animMap;			// アニメーション格納マップ
	STATE _state;									// 状態
	DIR _dir;										// 方向
	unsigned int _animFrame;						// 現在のコマ数
	unsigned int _animCount;						// アニメーションが始まってからのフレーム数のカウント
	int _effectID;									// ｴﾌｪｸﾄのﾊﾝﾄﾞﾙ保存しておく
protected:
	
	bool DestroyProc(void);			// 生存状態確認,死亡状態設定
	virtual void DrawHP(void);				// HPバー描画関数、操作するPlayerではUI上に描画したいのでoverrideする
	static int _hpBarImg[2];		// Obj共通のHPバー画像
	static int _shadowImg;			// 影画像ID

	bool _alive;					// 生存してるか(かつ爆発していない)
	bool _dead;						// 死亡してるか(かつ爆発が終了した)
	bool _exFlag;					// 特殊行動フラグ(Enemy:突撃開始,Player:キャプチャされる,など)
	bool _holdFlag;					// 持たれているか
	bool _glowFlag;					// エフェクトをかけるか
	int _hp;						// 体力
	int _hpMax;						// 最大体力
	int _power;						// 攻撃力
	UNIT_ID _unitID;				// 種別
	Vector2Dbl _pos;				// 座標
	Vector2Int _size;				// サイズ
	Vector2Dbl _vel;				// 速度、今は投げられるときに使う

	int _zOrder;					// 描画優先度
	int _weight;					// 重さ
	int _damageCnt;					// ダメージを受けた後のHPバー表示時間調整用
	int _glowID;					// 描画エフェクトをかけるためのスクリーン
	int _hpID;						// HPバー表示のためのスクリーン
	int _serialNum;					// 通し番号
	double _height;					// 高さ
	double _gravity;				// 投げられてるときの重力
	double _rad;					// 回転角
	double _speed;					// 速さ
	double _searchRange;			// 索敵範囲
	double _attackRange;			// 攻撃範囲
	TEAM_TAG _team;					// 陣営
	std::weak_ptr<Obj> _tageObj;	// 対象となるobj
	std::weak_ptr<Obj> _holdPlayer;	// 持たれているプレイヤー、持たれてないときは監視対象無し
	std::weak_ptr<Obj> _potObj;		// 壺
	std::map<STATE, funcObj> _funcState;	// オブジェクトの状態をキーにしてUpdateで行う関数を決定
	std::shared_ptr<InputState> _input;			// 入力管理クラス
	bool _effectFlg;							// ｴﾌｪｸﾄを連続再生していいかどうか
	int _coolCnt;								// ｸｰﾙﾀｲﾑ用
	int _coolCntMax;							// ｸｰﾙﾀｲﾑの最大値
};

