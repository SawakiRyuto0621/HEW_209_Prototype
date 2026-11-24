#pragma once
#include <DirectXMath.h>

class Player
{
private:
	float m_pos[3];
	float m_scale[3];
	DirectX::XMFLOAT3 m_moveSpeed;
	float m_turnAngle; // 旋回角度
	float m_upAngle;   // 上下角度
	bool m_bKeyPress;  // キーを押しているか（今は左右だけ）
	bool m_bTurn;      // 左右旋回フラグ
	bool m_bUpDown;    // 上下フラグ
	bool m_bBoost;     // 加速フラグ
	DirectX::XMFLOAT3 m_fSpeed; // Playerの速度を取得(現在は主にX)

public:
	Player();
	~Player();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	DirectX::XMFLOAT3 GetPos();
	float GetPosZ();
	void SetScale(float x, float y, float z);
	bool GetKeyPress();
	DirectX::XMFLOAT3 GetPlayerSpeed(); // Playerの速度を取得(現在は主にX)
	void AddSpeed(float x, float y, float z); //Playerに対する速度の変更
};