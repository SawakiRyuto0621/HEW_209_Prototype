#include "Stage.h"
#include "Wind.h"
#include <cstdlib>
#include <ctime>

Stage::Stage()
	: m_pos{ 0.0f, 0.0f, 0.0f }
	, m_scale{ 1.0f, 1.0f, 1.0f }
	, m_nWindStrength(0)
	, m_bWindDirectionRight(true)
	, m_nPreWindStrength(0)
	, m_bPreWindDirectionRight(true)
	, m_bCreateWind(false)
	, m_pWind(nullptr)
{
	m_bWindDirectionRight = rand() % 2 == 0; // 0‚©1
	m_nWindStrength = rand() % 3; // 0‚©1‚©2
	// •—
	m_pWind = new Wind(m_bWindDirectionRight, m_nWindStrength); // true‰EŒü‚«, false¶ // 0•’Ê1‹­2Žã
}

Stage::~Stage()
{
	if (m_pWind)// •—
	{
		delete m_pWind;
		m_pWind = nullptr;
	}
}

void Stage::Update()
{
	m_pWind->Update(); // •—
	if (m_pWind->bIsReborn())
	{
		if (m_pWind)
		{
			m_bPreWindDirectionRight = m_bWindDirectionRight;
			m_nPreWindStrength = m_nWindStrength;

			delete m_pWind;
			m_pWind = nullptr;

			while (!m_bCreateWind)
			{
				m_bWindDirectionRight = rand() % 2 == 0; // 0‚©1
				m_nWindStrength = rand() % 3; // 0‚©1‚©2

				if (m_bPreWindDirectionRight != m_bWindDirectionRight ||
					m_nPreWindStrength != m_nWindStrength) // ‚Ç‚Á‚¿‚ç‚ª•sˆê’v‚È‚ç
				{
					m_bCreateWind = true;
				}
			}
			m_bCreateWind = false;
			m_pWind = new Wind(m_bWindDirectionRight, m_nWindStrength); // true‰EŒü‚«, false¶ // 0•’Ê1‹­2Žã
		}
	}
}

void Stage::Draw()
{
	m_pWind->Draw(); // •—
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

float Stage::GetWindPosZ()
{
	return m_pWind->GetPosZ();
}

float Stage::GetWindWidth()
{
	return m_pWind->GetWidth();
}

bool Stage::GetWindDirectionRight()
{
	return m_pWind->GetWindDirectIonRight();
}
