#include <algorithm>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "SceneMng.h"
#include <_DebugDispOut.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "NetWork/NetWork.h"
#include "../common/EffectMng.h"
#include "../Map.h"

std::unique_ptr<SceneMng, SceneMng::SceneMngDeleter> SceneMng::sInstance(new SceneMng());

void SceneMng::Run(void)
{
	SysInit();
	
	_activeScene = std::make_unique<GameScene>();
	_dbgStartFPS();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		lpNetWork.Connect();
		_drawList.clear();
		lpNetWork.UpDate();

		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		(*_activeScene).RunInstanceQue(std::move(_instanceList));
		(*_activeScene).RunActQue(std::move(_actList));
		lpMap.Draw();
		Draw();
		_frameCnt++;
		lpNetWork.ReSetRecMes();
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// �摜ID���s���Ȃ̂Œǉ����Ȃ�
		return false;
	}
	// Que��ǉ�
	_drawList.emplace_back(dQue);
	return true;
}


bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

bool SceneMng::AddSoundQue(SoundQueT sQue)
{
	if (std::get<static_cast<int>(SOUND_QUE::SOUND)>(sQue) <= 0)
	{
		// SoundID���s���Ȃ̂Œǉ����Ȃ�
		return false;
	}
	// Que��ǉ�
	_soundList.emplace_back(sQue);
	return true;
}

bool SceneMng::AddPlayerQue(PlayerQueT pQue)
{
	_playerList.emplace_back(pQue);
	return true;
}

bool SceneMng::AddInstanceQue(InstanceQueT iQue)
{
	UNIT_ID id;
	int type, num;
	Vector2Dbl pos;

	std::tie(id, type, pos, num) = iQue;

	num = _serialNumCnt;
	_serialNumCnt++;

	_instanceList.emplace(_instanceList.begin(), InstanceQueT{id,type,pos,num});
	return false;
}

const size_t SceneMng::GetPlayerListSize(void) const
{
	return _playerList.size();
}

std::vector<PlayerQueT>& SceneMng::playerList(void)
{
	return _playerList;
}

void SceneMng::FrameCntReset(void)
{
	_frameCnt = 0;
}

const int SceneMng::frameCnt(void) const
{
	return _frameCnt;
}

int SceneMng::serialNumCnt(void)
{
	return _serialNumCnt;
}

void SceneMng::AddSerialNum(void)
{
	_serialNumCnt++;
}

bool SceneMng::SetInstanceQue(InstanceQueT iQue)
{
	_instanceList.emplace_back(iQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	// --------- �V�X�e������
	SetWindowText("Alchemy");

	SetGraphMode(static_cast<int>(ScreenSize.x), static_cast<int>(ScreenSize.y), 16);
	ChangeWindowMode(true);

	SetUseDirect3DVersion(DX_DIRECT3D_11);					// DIRECTX11���g����悤�ɂ���

	if (DxLib_Init() == -1)
	{
		return false;
	}

	if (Effekseer_Init(6000) == -1)
	{
		DxLib_End();
		return false;
	}

	// ��ذ݂̐؂�ւ���ؿ����������̂�h���B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXײ���؂����޲�۽Ă������̺���ޯ���ݒ肷��
	// ����޳���ٽ�ذ݂̐؂�ւ�����������ꍇ�ɂ͕K�����s����
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// �`��X�N���[���쐬
	_layerGID = MakeScreen(static_cast<int>(ScreenSize.x), static_cast<int>(ScreenSize.y), true);
	SetDrawScreen(DX_SCREEN_BACK);

	// Effekseer�ɕ`��̐ݒ������
	Effekseer_Set2DSetting(static_cast<int>(WorldSize.x), static_cast<int>(WorldSize.y));
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	_dbgSetup(255);

	_frameCnt = 0;
	lpNetWork.NetMode(NETMODE::HOST);						// �޽�Ӱ�ސݒ� νĂ�Labo��
	return false;
}

SceneMng::SceneMng() :ScreenSize{ 1280.0,720.0 }, ScreenCenter(ScreenSize / 2.0), WorldSize{ 2560.0,1440.0 }, WorldCenter(WorldSize / 2.0)
{
}

SceneMng::~SceneMng()
{
}

void SceneMng::Draw(void)
{
	_dbgAddDraw();	// ���ޯ�ނ̷���𓊂���

	// DrawؽĂ̿��
	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT queA, DrawQueT queB) {
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(queA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(queA), std::get<static_cast<int>(DRAW_QUE::Y)>(queA)) <
			std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(queB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(queB), std::get<static_cast<int>(DRAW_QUE::Y)>(queB));
	});


	// �`��X�N���[����������
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	LAYER drawLayer = begin(LAYER());
	int blendMode = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 255;

	SetDrawScreen(_layerGID);
	SetDrawBlendMode(blendMode, blendModeNum);
	ClsDrawScreen();

	// ���܂��Ă���DrawQue�����ꂼ��̃��C���[�ɕ`�悷��
	for (auto que : _drawList)
	{
		double x, y, rad;
		int id;
		LAYER layer;

		double rate;		// �摜�̊g�嗦
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		std::tie(id, x, y, rad, rate, std::ignore, layer, blendMode, blendModeNum) = que;

		/*if ((layer != drawLayer) || (blendMode != blendModeOld) || (blendModeNum != blendModeNumOld))
		{
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(static_cast<int>(layPos.x), static_cast<int>(layPos.y), 1.0, 0, _layerGID, true);

			SetDrawScreen(_layerGID);
			SetDrawBlendMode(blendMode, blendModeNum);
			ClsDrawScreen();
		}*/

		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			rate,
			rad,
			id,
			true
		);
	}
	// ���ꂼ��̃��C���[��`�悷��
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(blendMode, blendModeNum);
	DrawRotaGraph(static_cast<int>(ScreenCenter.x), static_cast<int>(ScreenCenter.y), 1.0, 0, _layerGID, true);

	//_dbgDrawFPS();
	ScreenFlip();
}
