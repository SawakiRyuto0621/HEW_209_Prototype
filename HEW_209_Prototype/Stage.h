#pragma once

// Stage関連はSceneGameからここに

class Wind;

class Stage
{
private:
	float m_pos[3];
	float m_scale[3];
private:
	int m_nWindStrength; // 風の強度をランダム生成用(０普通、１強、２弱)
	bool m_bWindDirectionRight; // 風の向きをランダム生成用(true右向き)
	int m_nPreWindStrength; // 一致の風が２回生成しないための記録
	bool m_bPreWindDirectionRight; // 一致の風が２回生成しないための記録
	bool m_bCreateWind; // 一致の風が２回生成しないためのフラグ
	float m_fSpeed[3];
	float m_fAddedSpeed[3];
	int m_nStageSpeedRatio; // stageの現在速度 / 最低速度の倍率
	Wind* m_pWind; // 風

public:
	Stage();
	~Stage();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	float GetSpeedZ();
	void SetSpeed(float x, float y, float z); // Stageに従属するオブジェクトの
	void AddSpeed(float x, float y, float z); // 変更分の速度
	float GetWindPosZ(); // 風の中心の Z座標を取得
	float GetWindWidth(); // 風の Z軸方向の横幅
	bool GetWindDirectionRight(); // 風の向きが右か取得
	int GetWindStrength();
};