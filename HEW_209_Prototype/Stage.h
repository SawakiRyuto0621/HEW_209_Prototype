#pragma once

// StageŠÖ˜A‚ÍSceneGame‚©‚ç‚±‚±‚É

class Wind;

class Stage
{
private:
	float m_pos[3];
	float m_scale[3];
	int m_nWindStrength;
	bool m_bWindDirectionRight;
	int m_nPreWindStrength;
	bool m_bPreWindDirectionRight;
	bool m_bCreateWind;
	Wind* m_pWind; // •—

public:
	Stage();
	~Stage();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	float GetWindPosZ();
	float GetWindWidth();
	bool GetWindDirectionRight();
};