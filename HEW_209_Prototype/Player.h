#pragma once
#include <DirectXMath.h>

class Player
{
private:
	float m_pos[3];
	float m_scale[3];
	float m_angle;
	bool m_bKeyPress; // キーを押しているか（今は左右だけ）
	bool m_bTurn; // 左右旋回フラグ
	DirectX::XMFLOAT3 m_fSpeed; // Playerの速度を取得(現在は主にX)

public:
	Player();
	~Player();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	float GetPosZ();
	void SetScale(float x, float y, float z);
	bool GetKeyPress(); // キーを押しているか（今は左右だけ）
	DirectX::XMFLOAT3 GetPlayerSpeed(); // Playerの速度を取得(現在は主にX)
	
};