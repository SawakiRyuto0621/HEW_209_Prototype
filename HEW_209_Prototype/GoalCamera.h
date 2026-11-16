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

private:
	float m_radXZ; //カメラの横回転
	float m_radY;  // カメラの縦回転
	float m_radius; //カメラと注視点の距離

};