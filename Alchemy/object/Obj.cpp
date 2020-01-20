#include <DxLib.h>
#include <Scene\SceneMng.h>
#include "Obj.h"
#include <_DebugConOut.h>
#include "Camera.h"

Obj::Obj()
{
	_alive = true;
	_dead = false;
	_holdFlag = false;
	_animFrame = 0;
	_animCount = 0;
	_speed = 0.0;
	_rad = 0.0;
	_zOrder = 0;
	_height = 0;
	_holdFlag = false;
	_effectFlg = false;
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

	if ((_pos.x >= lpCamera.pos().x - lpCamera.size().x) &&
		(_pos.x <= lpCamera.pos().x + lpCamera.size().x) &&
		(_pos.y >= lpCamera.pos().y - lpCamera.size().y) &&
		(_pos.y <= lpCamera.pos().y + lpCamera.size().y)
		)
	{
		// 現在のコマの画像を描画キューに追加
		lpSceneMng.AddDrawQue({ _animMap[{ _state ,_dir}][_animFrame].first,
			_pos.x - lpCamera.OfSet().x,
			_pos.y - _height - lpCamera.OfSet().y,
			0.0,
			_zOrder,
			LAYER::CHAR ,
			DX_BLENDMODE_NOBLEND,
			255 });

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
			_pos.y - _height - lpCamera.OfSet().y,
			0.0,_zOrder - 1,LAYER::CHAR,DX_BLENDMODE_ADD,255 });

		_glowFlag = false;
	}

}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,
							_pos.x,
					        _pos.y - _height,
					        _rad,
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

// 生存状態確認,死亡状態設定
bool Obj::DestroyProc(void)
{
	if (alive())
	{
		return false;
	}

	if (isAnimEnd())
	{
		dead(true);
	}

	return true;
}
