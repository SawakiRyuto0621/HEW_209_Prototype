#pragma once
#include "Camera.h"

class Player;

class CameraPlayer : public Camera {
private:
	// デバッグカメラで追加していた各種パラメータ
	float m_radXZ; //  カメラの横回転
	float m_radY;   // カメラの縦回転
	float m_radius; //  カメラと注視点の距離

	Player* m_pPlayer; // 追いかけるプレイヤー 

public:
	// 基本の処理 
	CameraPlayer();
	~CameraPlayer();

	// 更新処理 
	void Update() final;

	// カメラが追いかけるプレイヤーを設定 
	void SetPlayer(Player* player);
};