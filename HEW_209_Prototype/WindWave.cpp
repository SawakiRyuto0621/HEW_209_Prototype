#include "WindWave.h"
#include "WindParticles.h"
#include "Wind.h"

constexpr int WindParticlesNum = 8;

WindWave::WindWave(float posZ, bool directionRight)
	: m_pWindParticles{ nullptr, nullptr, nullptr }
	, m_pos{ 0.0f, 0.0f, posZ} // Windの Z座標で初期化
	, m_scale{ 1.0f, 1.0f, 1.0f }
	, m_bDirectionRight(directionRight)
{
	m_pWindParticles[0] = new WindParticles(posZ, directionRight, 0); // Z座標を渡す、向き指定、pattern指定
	m_pWindParticles[1] = new WindParticles(posZ, directionRight, 1);
	m_pWindParticles[2] = new WindParticles(posZ, directionRight, 2);
}

WindWave::~WindWave()
{
	for (int i = 0; i < 3; i++)
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
	for (int i = 0; i < 3; i++)
	{
		m_pWindParticles[i]->Update();
	}
	if (m_pWindParticles[1]->bReborn()) // 奥のパーティクルもstart check状態なら
	{
		for (int i = 0; i < 3; i++)
		{
			m_pWindParticles[i]->SetReborn(false);
		}
	}
}

void WindWave::Draw()
{
	for (int i = 0; i < 3; i++)
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