#include "WindWave.h"
#include "WindParticles.h"
#include "Wind.h"

// ********************  開発履歴  ********************
// 2026/11/14  *****  陳  *****  クラス作成
// 2026/11/15  *****  陳  *****  風（パーティクル）が指定の向きに曲線移動
// 2026/11/16  *****  陳  *****  強度指定、ランダムパターンで風の生成、再生成
// 2026/11/17  *****  陳  *****  風の X座標移動速度が stageの移動速度に比例する

WindWave::WindWave(float posZ, bool directionRight, float width, int strength)
	: m_pWindParticles{ nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr}
	, m_pos{ 0.0f, 0.0f, posZ} // Windの Z座標で初期化
	, m_scale{ 1.0f, 1.0f, 1.0f }
	, m_bDirectionRight(directionRight)
	, m_bReborn(false)
{
	m_pWindParticles[0] = new WindParticles(posZ, directionRight, width, 0, strength); // Z座標を渡す、向き指定、位置前後pattern指定
	m_pWindParticles[1] = new WindParticles(posZ, directionRight, width, 1, strength); // Z座標を渡す、向き指定、位置前後pattern指定
	m_pWindParticles[2] = new WindParticles(posZ, directionRight, width, 2, strength); // Z座標を渡す、向き指定、位置前後pattern指定
	m_pWindParticles[3] = new WindParticles(posZ, directionRight, width, 3, strength);
	m_pWindParticles[4] = new WindParticles(posZ, directionRight, width, 4, strength);
	m_pWindParticles[5] = new WindParticles(posZ, directionRight, width, 5, strength);
	m_pWindParticles[6] = new WindParticles(posZ, directionRight, width, 6, strength);
	m_pWindParticles[7] = new WindParticles(posZ, directionRight, width, 7, strength);
	m_pWindParticles[8] = new WindParticles(posZ, directionRight, width, 8, strength);
}

WindWave::~WindWave()
{
	for (int i = 0; i < WindParticlesNum; i++)
	{
		if (m_pWindParticles[i])
		{
			delete m_pWindParticles[i];
			m_pWindParticles[i] = nullptr;
		}
	}
}

void WindWave::Update()
{
	for (int i = 0; i < WindParticlesNum; i++)
	{
		m_pWindParticles[i]->Update();

		if (!m_pWindParticles[i]->bReborn()) continue;
		m_bReborn = true;
	}
}

void WindWave::Draw()
{
	for (int i = 0; i < WindParticlesNum; i++)
	{
		 m_pWindParticles[i]->Draw();
	}
}

void WindWave::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

void WindWave::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

bool WindWave::bIsReborn()
{
	return m_bReborn;
}

void WindWave::SetAccelerateWithPlayer(float acceleration)
{
	for (int i = 0; i < WindParticlesNum; i++)
	{
		m_pWindParticles[i]->SetAccelerateWithPlayer(acceleration);
	}
}
