#include "Stage.h"
#include "Wind.h"

Stage::Stage()
	: m_pos{ 0.0f, 0.0f, 0.0f }
	, m_scale{ 1.0f, 1.0f, 1.0f }
	, m_pWind(nullptr)
{

	// •—
	m_pWind = new Wind(true); // true‰EŒü‚«, false¶
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
