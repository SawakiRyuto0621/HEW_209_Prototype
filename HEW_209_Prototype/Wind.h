#pragma once

class WindWave;
class WindArea;

class Wind
{
private:
	float m_pos[3];
	float m_scale[3];
	bool m_bDirectionRight; // ‰EŒü‚«‚©
	WindWave* m_pWindWave;
	WindArea* m_pWindArea;

public:
	Wind(bool directionRight);
	~Wind();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	float GetPosZ(); // ZÀ•W
	void SetScale(float x, float y, float z);
};