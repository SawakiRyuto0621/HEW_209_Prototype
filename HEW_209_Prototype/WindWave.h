#pragma once
#include <float.h>

class WindParticles;

class WindWave
{
private:
	float m_pos[3];
	float m_scale[3];
	bool m_bDirectionRight; // 右向きか
	WindParticles* m_pWindParticles[3]; // ***** 一旦3つのパーティクルを作成した *****

public:
	WindWave(float posZ, bool directionRight);
	~WindWave();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
};