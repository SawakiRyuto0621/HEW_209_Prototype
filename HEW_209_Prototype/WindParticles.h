#pragma once

class WindParticles
{
private:
	float m_pos[3];
	float m_scale[3];
	float m_fSpeed[3];
	float m_fStartPos[3];
	float m_fPaPos[3];
	float m_fPbPos[3];
	float m_fEndPos[3];
	float m_fStartZ_Pos;
	float m_fWaveCnt; // ベジェ曲線用カウント
	float m_fWindWidth;
	float m_fAccelerateWithPlayer;
	float m_fPosChangeBySpeedX;
	int m_nFrontBackPattern;
	int m_nStrength;
	bool m_bDirectionRight; // 右に向くか
	bool m_bReborn;

public:
	WindParticles(float posZ, bool directionRight,float width, int pattern, int strength);
	~WindParticles();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetSpeed(float x, float y, float z);
	void PosChangeBySpeed(float x, float y, float z);
	bool bReborn();
	void ConstructorWindNormal();
	void ConstructorWindStrong();
	void ConstructorWindWeak();
	void SetAccelerateWithPlayer(float acceleration);
	void ParticlesLocation();
};