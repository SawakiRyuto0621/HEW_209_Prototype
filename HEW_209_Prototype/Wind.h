#pragma once
#include "DirectX.h"

class WindWave;
class WindArea;

class Wind
{
private:
	float m_pos[3];
	float m_scale[3];
	float m_fWindWidth;
	bool m_bDirectionRight; // 右向きか
	WindWave* m_pWindWave;
	WindArea* m_pWindArea;

public:
	Wind(float posX, bool directionRight, int strength); // 右向きか、強度
	~Wind();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	float GetPosX();
	float GetPosZ(); // Z座標
	float GetWidth();
	void SetScale(float x, float y, float z);
	void SetSpeed(float x, float y, float z);
	bool GetWindDirectIonRight();
	bool bIsReborn();
	void SetAccelerateWithPlayer(float acceleration); // 風の X座標移動速度が stageの Z移動速度と比例する
};