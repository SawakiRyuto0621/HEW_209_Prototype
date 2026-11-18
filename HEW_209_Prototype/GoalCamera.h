#pragma once

#include "Camera.h"

class GoalCamera : public Camera
{
public:
	//コンストラクタ
	GoalCamera();
	//デストラクタ
	~GoalCamera();
	void Update() final;

	void Start(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 look); // 演出開始位置
	void Stop(); // 停止
	void MoveGoalCamera();


	bool GetGoalflag();

private:
	float m_radXZ; //カメラの横回転
	float m_radY;  // カメラの縦回転
	float m_radius; //カメラと注視点の距離

private:
	DirectX::XMFLOAT3 m_startPos;
	DirectX::XMFLOAT3 m_startLook;
	bool m_goalFlag;
};