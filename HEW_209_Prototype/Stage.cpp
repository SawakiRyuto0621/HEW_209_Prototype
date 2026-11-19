#include "Stage.h"
#include "Wind.h"
#include <cstdlib>
#include <ctime>
#include "Defines.h"

// ********************  開発履歴  ********************
// 2026/11/14  *****  陳  *****  クラス作成
// 2026/11/15  *****  陳  *****  風（パーティクル）が指定の向きに曲線移動
// 2026/11/16  *****  陳  *****  強度指定、ランダムパターンで風の生成、再生成
// 2026/11/17  *****  陳  *****  風の X座標移動速度が stageの移動速度に比例する
//#ifdef _DEBUG
//constexpr float g_testZ_Speed_Ratio = 3.0f; // テスト用、現在速度 / 最低速度の倍率
//#endif


Stage::Stage()
	: m_pos{ 0.0f, 0.0f, 0.0f }
	, m_scale{ 1.0f, 1.0f, 1.0f }
	, m_fSpeed {0.0f, 0.0f, METER(20.0f * 1000) / (FPS * 60 * 60)}
	, m_fAddedSpeedFromPlayerX(0.0f)
	, m_fAddedSpeedFromPlayerY(0.0f)
	, m_fAddedSpeedFromPlayerZ(0.0f)
	, m_fWindEndPosX(0.0f)
	, m_nWindStrength(0) // 風の強度をランダム生成用(０普通、１強、２弱)
	, m_bWindDirectionRight(true) // 風の向きをランダム生成用(true右向き)
	, m_nPreWindStrength(0) // 一致の風が２回生成しないための記録
	, m_bPreWindDirectionRight(true) // 一致の風が２回生成しないための記録
	, m_bCreateWind(false) // 一致の風が２回生成しないためのフラグ
	, m_nStageSpeedRatio(1) // stageの現在速度 / 最低速度の倍率
	, m_pWind(nullptr) // 風
{
	m_bWindDirectionRight = rand() % 2 == 0; // 0か1
	m_nWindStrength = rand() % 3; // 0か1か2
	// 風
	m_pWind = new Wind(m_fWindEndPosX, m_bWindDirectionRight, m_nWindStrength); // true右向き, false左 // 0普通1強2弱
	SetWindAccelerateWithPlayer();
}

Stage::~Stage()
{
	if (m_pWind)// 風
	{
		delete m_pWind;
		m_pWind = nullptr;
	}
}

void Stage::Update()
{
	SetSpeed(m_fSpeed[0], m_fSpeed[1], m_fSpeed[2]);
	m_pWind->Update(); // 風
	if (m_pWind->bIsReborn()) // カメラの後ろに、Reborn状態
	{
		if (m_pWind)
		{
			m_fWindEndPosX = m_pWind->GetPosX();
			m_bPreWindDirectionRight = m_bWindDirectionRight; // 前の風の向き更新
			m_nPreWindStrength = m_nWindStrength; // 前の風の強度更新

			delete m_pWind; // 後片付け
			m_pWind = nullptr;

			while (!m_bCreateWind) // 完全一致の風が２回生成しないためのフラグ
			{
				m_bWindDirectionRight = rand() % 2 == 0; // 0か1
				m_nWindStrength = rand() % 3; // 0か1か2

				// 向きが毎回違うように設定
				if (m_bPreWindDirectionRight != m_bWindDirectionRight /*||
					m_nPreWindStrength != m_nWindStrength*/) // どっちらが不一致なら
				{
					m_bCreateWind = true; // ループ脱出
				}
			}
			m_bCreateWind = false; // フラグを戻す
			m_pWind = new Wind(m_fWindEndPosX, m_bWindDirectionRight, m_nWindStrength); // 再生成
			SetWindAccelerateWithPlayer();
		}
	}
	else if ((int)(m_fSpeed[2] / (METER(5.0f * 1000) / (FPS * 60 * 60)))
		- m_nStageSpeedRatio >= 1) // ******** (現在速度 / 最低速度)を入れる
	{ // 現在速度が前の倍率より一倍以上速くなった
		m_nStageSpeedRatio += (int)(m_fSpeed[2] - m_nStageSpeedRatio); // ******** 現在速度を入れる // 倍率更新
		SetWindAccelerateWithPlayer(); // 風の X座標移動速度が stageの Z移動速度と比例する
	}
	else if (m_nStageSpeedRatio - 
		(int)(m_fSpeed[2] / (METER(5.0f * 1000) / (FPS * 60 * 60))) >= 1) // ******** (現在速度 / 最低速度)を入れる
	{// 現在速度が前の倍率より一倍以上遅くなった
		m_nStageSpeedRatio -= abs((int)(m_fSpeed[2] - m_nStageSpeedRatio)); // ******** 現在速度を入れる // 倍率更新
		SetWindAccelerateWithPlayer(); // 風の X座標移動速度が stageの Z移動速度と比例する
	}
}

void Stage::Draw()
{
	m_pWind->Draw(); // 風
}

void Stage::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

void Stage::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

void Stage::SetSpeed(float x, float y, float z) // **********************************************************************
{
	m_pWind->SetSpeed(m_fSpeed[0] + m_fAddedSpeedFromPlayerX
					, m_fSpeed[1] + m_fAddedSpeedFromPlayerY
					, m_fSpeed[2] + m_fAddedSpeedFromPlayerZ);

}

void Stage::AddSpeedFromPlayer(float x, float y, float z)
{
	m_fAddedSpeedFromPlayerX = x;
	m_fAddedSpeedFromPlayerY = y;
	m_fAddedSpeedFromPlayerZ = z;
}

float Stage::GetWindPosZ() // 風の中心の Z座標を取得
{
	return m_pWind->GetPosZ();
}

float Stage::GetWindWidth() // 風の Z軸方向の横幅
{
	return m_pWind->GetWidth();
}

bool Stage::GetWindDirectionRight() // 風の向きが右か取得
{
	return m_pWind->GetWindDirectIonRight();
}

void Stage::SetWindAccelerateWithPlayer()
{
	m_pWind->SetAccelerateWithPlayer(m_nStageSpeedRatio); // playerの現在速度/最低速度の倍率
}
