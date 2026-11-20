#pragma once
#include <float.h>

constexpr int WindParticlesNum = 15;

class WindParticles;

class WindWave
{
private:
	float m_pos[3];
	float m_scale[3];
	float m_speed[3];
	bool m_bDirectionRight; // 右向きか
	bool m_bReborn;
	WindParticles* m_pWindParticles[WindParticlesNum]; // ***** パーティクルを作成した *****

public:
	WindWave(float posZ, bool directionRight, float width, int strength, float speedZ);
	~WindWave();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetSpeed(float x, float y, float z);
	bool bIsReborn();
};