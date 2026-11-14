#pragma once

// Stage関連はSceneGameからここに

class WindParticles;

class Stage
{
private:
	float m_pos[3];
	float m_scale[3];

	WindParticles* m_pWindParticles; // 風のパーティクル

public:
	Stage();
	~Stage();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
};