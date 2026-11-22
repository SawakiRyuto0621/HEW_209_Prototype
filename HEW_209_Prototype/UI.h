#pragma once
#include <DirectXMath.h>

class SpeedMeter;

class UI
{
private:
	SpeedMeter* m_pSpeedMeter;

public:
	UI();
	~UI();
	void Update();
	void Draw();
	void SetSpeed(int speed);
};