#include <DxLib.h>
#include <Scene\SceneMng.h>
#include "Obj.h"
#include <_DebugConOut.h>
#include "Camera.h"

int Obj::_hpBarImg[2] = {0,0};
int Obj::_shadowImg = 0;

Obj::Obj()
{
	_alive = true;
	_dead = false;
	_holdFlag = false;
	_animFrame = 0;
	_animCount = 0;
	_speed = 0.0;
	_size = { 100,100 };
	_rad = 0.0;
	_zOrder = 0;
	_effectID = -1;
	_height = 0;
	_holdFlag = false;
	_effectFlg = false;
	_damageCnt = 0;
	_hpMax = 0;
	_hp = 0;
	_hpID = MakeScreen(64, 8, false);
	_coolCnt = 0;
	_state = STATE::NORMAL;
	_dir = DIR::DOWN;
}

void Obj::Draw(void)
{
	// ---------- 範囲チェック
	if (_animMap.find({ _state ,_dir}) == _animMap.end())
	{
		AST();
		return;
	}
	
	if (_animFrame >= _animMap[{ _state, _dir}].size() || _animFrame < 0)
	{
		AST();
		return;
	}

	// アニメーションのコマ数の更新確認
	if (_animCount >= _animMap[{ _state, _dir}][_animFrame].second)
	{
		// ワンショットの確認
		if (_animMap[{ _state, _dir}][_animFrame].first != -1)
		{
			_animFrame++;
		}
	}

	// アニメーションループの確認
	if (_animFrame < _animMap[{ _state, _dir}].size())
	{
		_animCount++;
	}
	else
	{
		_animFrame = 0;
		_animCount = 0;
	}

	//// 現在のコマの画像を描画キューに追加

	if ((_pos.x >= lpCamera.pos().x - lpCamera.size().x - _size.x) &&
		(_pos.x <= lpCamera.pos().x + lpCamera.size().x + _size.x) &&
		(_pos.y >= lpCamera.pos().y - lpCamera.size().y - _size.y) &&
		(_pos.y <= lpCamera.pos().y + lpCamera.size().y + _size.y)
		)
	{
		// 現在のコマの画像を描画キューに追加
		lpSceneMng.AddDrawQue({ _animMap[{ _state ,_dir}][_animFrame].first,
			_pos.x - lpCamera.OfSet().x,
			_pos.y - lpCamera.OfSet().y,
			0.0,
			1.2 + (_height /400.0),
			_height,
			_zOrder,
			LAYER::CHAR ,
			DX_BLENDMODE_NOBLEND,
			255 });

		// HPバー
		DrawHP();
	}

	// エフェクトをかける
	if (_glowFlag)
	{
		SetDrawScreen(_glowID);
		ClsDrawScreen();
		SetDrawBright(255, 255, 0);
		DrawRotaGraph(_size.x, _size.y, 1.1, 0, _animMap[{_state, _dir}][_animFrame].first, true);
		SetDrawBright(255, 255, 255);
		GraphFilter(_glowID, DX_GRAPH_FILTER_GAUSS, 8, 100);
		GraphFilter(_glowID, DX_GRAPH_FILTER_TWO_COLOR, 10, 0, 0, 0xffffff, 255);
		lpSceneMng.AddDrawQue({ _glowID,_pos.x - lpCamera.OfSet().x,
			_pos.y - lpCamera.OfSet().y - 0.1,
			0.0,1.2,_height,_zOrder,LAYER::CHAR,DX_BLENDMODE_ADD,255 });

		_glowFlag = false;
	}
	else
	{
		// 影も描写
		// 高さによって大きさを変えたりするかも
		if (static_cast<int>(_state) < static_cast<int>(STATE::HOLDEN))
		{
			lpSceneMng.AddDrawQue({ _shadowImg,
			_pos.x - lpCamera.OfSet().x,
			_pos.y + _size.y / 2.0 - lpCamera.OfSet().y,
			0.0,
			1.2 - (_height / 400.0),
			0.0,
			INT_MIN,
			LAYER::CHAR ,
			DX_BLENDMODE_NOBLEND,
			255 });
		}
	}

}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,
							_pos.x,
					        _pos.y,
					        _rad,
							1.2,
							_height,
							_zOrder,
							LAYER::CHAR, 
							DX_BLENDMODE_NOBLEND, 
							255
	});
}


Obj::~Obj()
{
}

// STATEのget,set
// get
STATE Obj::state(void) const
{
	return _state;
}

// set
bool Obj::state(STATE newState)
{
	if (_animMap.find({ newState,_dir }) == _animMap.end())
	{
		// 登録したアニメーションのキーの中に存在しない
		AST();
		return false;
	}

	// 現在と同じアニメーションの時はコマ数とカウントをクリアしない
	if (_state != newState)
	{
		_animFrame = 0;
		_animCount = 0;
	}

	_state = newState;

	return true;
}

DIR Obj::dir(void)const
{
	return _dir;
}

bool Obj::dir(DIR newDir)
{
	if (_animMap.find({ _state,newDir }) == _animMap.end())
	{
		// 登録したアニメーションのキーの中に存在しない
		AST();
		return false;
	}

	// 現在と同じアニメーションの時はコマ数とカウントをクリアしない
	if (_dir != newDir)
	{
		_animFrame = 0;
		_animCount = 0;
	}

	_dir = newDir;

	return true;
}

bool Obj::alive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		_zOrder = 10;
		state(STATE::DEATH);
	}
	return true;
}

// _deadはメンバからしか変更しないからいらないかも
// _aliveはsetを使ってるからそれに合わせて一応
bool Obj::dead(bool dead)
{
	if (alive())
	{
		// 現状爆発が終了した時しか使わないので生存しているときは値を設定しない
		return false;
	}

	_dead = dead;

	return true;
}

const Vector2Dbl& Obj::pos(void)
{
	return _pos;
}

const Vector2Int & Obj::size(void)
{
	return _size;
}

const double & Obj::rad(void)
{
	return _rad;
}

void Obj::exFlag(bool isEX)
{
	_exFlag = isEX;

	return;
}

int Obj::getType(void)
{
	return 0;
}

void Obj::glowFlag(bool isGlow)
{
	_glowFlag = isGlow;
}

const int Obj::weight(void)
{
	return _weight;
}

const UNIT_ID & Obj::unitID(void)
{
	return _unitID;
}

const TEAM_TAG & Obj::teamTag(void)
{
	return _team;
}

std::weak_ptr<Obj>& Obj::tageObj(void)
{
	// 対象のobjを返す
	return _tageObj;
}

void Obj::SetTageObj(sharedObj obj)
{
	_tageObj = obj;
}

const double & Obj::searchRange(void)
{
	return _searchRange;
}

const double & Obj::attackRange(void)
{
	return _attackRange;
}

void Obj::DoDamage(int power)
{
	_hp -= power;
	if (_hp > _hpMax)
	{
		_hp = _hpMax;
	}
	_damageCnt = 180;
}

const int & Obj::hp(void)
{
	return _hp;
}

const int & Obj::hpMax(void)
{
	return _hpMax;
}

bool Obj::isAnimEnd(void)
{
	// ---------- 範囲チェック
	if (_animMap.find({ _state ,_dir }) == _animMap.end())
	{
		AST();
		return true;
	}

	if (_animFrame >= _animMap[{ _state, _dir}].size() || _animFrame < 0)
	{
		AST();
		return true;
	}

	if (_animMap[{ _state, _dir}][_animFrame].first == -1)
	{
		return true;
	}

	return false;
}

// アニメーションのデータを登録
bool Obj::SetAnim(const AnimKey key, AnimVector& data)
{
	return _animMap.try_emplace(key, std::move(data)).second;

	/*if (_animMap.find(key) == _animMap.end())
	{
		_animMap[key] = std::move(data);
		return true;
	}
	
	return false;*/
}

// オブジェで共通で使う画像を読み込む
// GameSceneのInitで壺オブジェから呼び出す
void Obj::LoadStaticImg(void)
{
	_hpBarImg[0] = lpImageMng.GetID({ IMG::HP_R ,STATE::NORMAL }, "image/unitHP_R.png")[0];
	_hpBarImg[1] = lpImageMng.GetID({ IMG::HP_G ,STATE::NORMAL }, "image/unitHP_G.png")[0];

	_shadowImg = lpImageMng.GetID({ IMG::SHADOW,STATE::NORMAL }, "image/shadow.png")[0];
}

// 生存状態確認,死亡状態設定
bool Obj::DestroyProc(void)
{
	if (alive())
	{
		return false;
	}
	else
	{
		if (_state != STATE::DEATH)
		{
			state(STATE::DEATH);
		}
	}


	if (isAnimEnd())
	{
		dead(true);
	}

	return true;
}

void Obj::DrawHP(void)
{
	// まず下に赤いバーを描画し、上に緑のバーをRectGraphで残りHPに従って描画
	if (_damageCnt > 0)
	{
		if (_hpMax != 0)
		{
			SetDrawScreen(_hpID);
			DrawGraph(0, 0, _hpBarImg[0], false);
			DrawRectGraph(0, 0, 0, 0, 64 * _hp / _hpMax, 8, _hpBarImg[1], false, false);
			SetDrawScreen(DX_SCREEN_BACK);

			lpSceneMng.AddDrawQue({ _hpID,
				_pos.x - lpCamera.OfSet().x,
				_pos.y-lpCamera.OfSet().y - 48,
				0.0,
				1.0,
				_height,
				_zOrder + 1,
				LAYER::UI ,
				DX_BLENDMODE_NOBLEND,
				255 });
			_damageCnt--;
		}
	}
}
