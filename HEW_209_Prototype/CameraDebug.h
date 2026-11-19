#pragma once
#include "Camera.h"
#include "GoalCamera.h"

//デバック用カメラ
class CameraDebug : public Camera
{
public:
	//コンストラクタ
	CameraDebug();
	//デストラクタ
	~CameraDebug();

	void Update() final;

private:
	float m_radXZ; //カメラの横回転
	float m_radY;  // カメラの縦回転
	float m_radius; //カメラと注視点の距離

	GoalCamera* m_pGoalCamera; // ゴール演出のカメラ
};