#pragma once

class Player
{
private:
	float m_pos[3];
	float m_scale[3];

public:
	Player();
	~Player();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	
};