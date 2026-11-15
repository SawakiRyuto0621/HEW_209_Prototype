#include "Wind.h"
#include "WindWave.h"
#include "WindArea.h"

Wind::Wind(bool directionRight)
	: m_pWindWave(nullptr)
	, m_pos{ 0.0f, 0.0f, 5.0f } // ‰Šú ZÀ•W‚ðÝ’è
	, m_scale{ 1.0f, 1.0f, 1.0f }
	, m_bDirectionRight(directionRight)
{
	m_pWindWave = new WindWave(m_pos[2], directionRight); // ZÀ•WAŒü‚«‚ð“n‚·
	m_pWindArea = new WindArea();
}

Wind::~Wind()
{
	if (m_pWindArea) {
		delete m_pWindArea;
		m_pWindArea = nullptr;
	}
	if (m_pWindWave) {
		delete m_pWindWave;
		m_pWindWave = nullptr;
	}
}

void Wind::Update()
{
	m_pWindWave->Update();
	m_pWindArea->Update();
}

void Wind::Draw()
{
	m_pWindWave->Draw();
	m_pWindArea->Draw();
}

void Wind::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

float Wind::GetPosZ()
{
	return m_pos[2];
}

void Wind::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

