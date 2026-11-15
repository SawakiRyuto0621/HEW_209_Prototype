#pragma once

class WindParticles
{
private:
	float m_pos[3];
	float m_scale[3];
	float m_fStartPos[3];
	float m_fPaPos[3];
	float m_fPbPos[3];
	float m_fEndPos[3];
	float m_fWaveCnt; // ベジェ曲線用カウント
	bool m_bDirectionRight; // 右に向くか
	bool m_bReborn;

public:
	WindParticles(float posZ, bool directionRight, int pattern);
	~WindParticles();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	bool bReborn();
	void SetReborn(bool b);
};