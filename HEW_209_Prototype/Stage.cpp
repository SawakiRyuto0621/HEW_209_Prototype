#include "Stage.h"
#include "WindParticles.h"

constexpr int WindParticlesNum = 8;

Stage::Stage()
	: m_pos{ 0.0f, 0.0f, 0.0f }
	, m_scale{ 1.0f, 1.0f, 1.0f }
	, m_pWindParticles(nullptr)
{

	// 風のパーティクル
	m_pWindParticles = new WindParticles;
	m_pWindParticles->SetPos(-5.0f, 0.0f, 0.0f);
	m_pWindParticles->SetScale(0.1f, 0.1f, 0.1f);
}

Stage::~Stage()
{
	if (m_pWindParticles) // 風のパーティクル
	{
		delete m_pWindParticles;
		m_pWindParticles = nullptr;
	}
}

void Stage::Update()
{
	m_pWindParticles->Update();
}

void Stage::Draw()
{
	m_pWindParticles->Draw(); // 風のパーティクル
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
