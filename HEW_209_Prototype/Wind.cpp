#include "Wind.h"
#include "WindWave.h"
#include "WindArea.h"
#include "defines.h"

constexpr float g_fWindWidth = METER(3.0f);

Wind::Wind(bool directionRight, int strength)
	: m_pWindWave(nullptr)
	, m_pos{ 0.0f, 0.0f, 5.0f } // ‰Šú ZÀ•W‚ðÝ’è
	, m_scale{ 1.0f, 1.0f, 1.0f }
	, m_fWindWidth(g_fWindWidth)
	, m_bDirectionRight(directionRight)
{
	m_pWindWave = new WindWave(m_pos[2], directionRight, m_fWindWidth, strength); // ZÀ•WAŒü‚«‚ð“n‚·
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

float Wind::GetWidth()
{
	return g_fWindWidth;
}

void Wind::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

bool Wind::GetWindDirectIonRight()
{
	return m_bDirectionRight;
}

bool Wind::bIsReborn()
{
	return m_pWindWave->bIsReborn();
}

void Wind::SetAccelerateWithPlayer(float acceleration)
{
	m_pWindWave->SetAccelerateWithPlayer(acceleration);
}

