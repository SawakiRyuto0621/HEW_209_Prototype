#include "UI.h"
#include "Sprite.h"
#include "SpeedMeter.h"

// ********************  開発履歴  ********************
// 2026/11/22  *****  陳  *****  UIで Speed Meterが表示される、速度も反映(Stageの仮速度)(最大200km/h)

UI::UI()
	: m_pSpeedMeter(nullptr)
{
	m_pSpeedMeter = new SpeedMeter();
}

UI::~UI()
{
	if (m_pSpeedMeter)
	{
		delete m_pSpeedMeter;
		m_pSpeedMeter = nullptr;
	}
}

void UI::Update()
{
	m_pSpeedMeter->Update();
}

void UI::Draw()
{
	m_pSpeedMeter->Draw();
}

void UI::SetSpeed(int speed)
{
	m_pSpeedMeter->SetSpeed(speed);
}
