#pragma once
#include <DirectXMath.h>

class Player
{
private:
	float m_pos[3];
	float m_scale[3];
	bool m_bKeyPress;
	DirectX::XMFLOAT3 m_fSpeed;

public:
	Player();
	~Player();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	float GetPosZ();
	void SetScale(float x, float y, float z);
	bool GetKeyPress();
	DirectX::XMFLOAT3 GetPlayerSpeed();
	
};