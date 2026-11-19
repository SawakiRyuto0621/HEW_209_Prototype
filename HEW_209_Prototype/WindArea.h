#pragma once

class WindArea
{
private:
	float m_pos[3];
	float m_scale[3];
	float m_fSpeed[3];
	float m_fAccelerateWithPlayer;

public:
	WindArea(float posZ, float width);
	~WindArea();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	float GetPosX();
	void SetScale(float x, float y, float z);
	void SetSpeed(float x, float y, float z);

};