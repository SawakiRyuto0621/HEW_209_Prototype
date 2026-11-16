#include "WindParticles.h"
#include "Geometory.h"
#include "Defines.h"

constexpr float g_fParticleSpeedX_Normal = METER(5.0f) / FPS; // ****** 一旦x座標移動速度の設定(1フレイムの移動量)(普通)
constexpr float g_fParticleSpeedX_Strong = METER(10.0f) / FPS; // ****** 一旦x座標移動速度の設定(1フレイムの移動量)(強)
constexpr float g_fParticleSpeedX_Weak = METER(3.0f) / FPS; // ****** 一旦x座標移動速度の設定(1フレイムの移動量)(弱)

constexpr float g_fParticleX_Distance = METER(5.0f);
constexpr float g_WaveX_Move = METER(10.0f);
constexpr float g_WaveY_Move_Normal = METER(3.0f); // 制御点の高さ->最高点約0.7m
constexpr float g_WaveY_Move_Strong = METER(1.0f); // 制御点の高さ->最高点約0.3m
constexpr float g_WaveY_Move_Weak = METER(1.5f); // 制御点の低さ->最低点約1.1m

#ifdef _DEBUG
constexpr float g_testZ_Speed = METER(0.02f);
#endif

WindParticles::WindParticles(float posZ, bool directionRight,float width, int pattern, int strength)
	: m_pos{ 5.0f, 1.5f, posZ} // ***** 初期位置座標を調整
	, m_scale{ 0.2f, 0.2f, 0.2f }
	, m_fWaveCnt(0.0f) // ベジェ曲線用カウント
	, m_fStartZ_Pos(posZ)
	, m_fStartPos{ 0.0f, 0.0f, posZ }
	, m_fPaPos{ 0.0f, 0.0f, posZ }
	, m_fPbPos{ 0.0f, 0.0f, posZ }
	, m_fEndPos{ 0.0f, 0.0f, posZ }
	, m_bDirectionRight(directionRight)
	, m_fWindWidth(width)
	, m_nFrontBackPattern(pattern)
	, m_nStrength(strength)
	, m_bReborn(false)
{
	switch(strength) // 強度によるベジェ曲線制御点初期化
	{
	case 0:
		ConstructorWindNormal(); // 普通
		break;
	case 1:
		ConstructorWindStrong(); // 強
		break;
	case 2:
		ConstructorWindWeak(); // 強と同じ曲線
		break;
	default:
		break;
	}

}

WindParticles::~WindParticles()
{
}

void WindParticles::Update()
{
	// ベジェ曲線
	if (m_fWaveCnt >= 1.0f) // 0から1
	{
		m_fWaveCnt = 0.0f;
	}
	else
	{
		m_pos[0] = m_fStartPos[0] * (1.0f - m_fWaveCnt) * (1.0f - m_fWaveCnt) * (1.0f - m_fWaveCnt)
			+ m_fPaPos[0] * (1.0f - m_fWaveCnt) * (1.0f - m_fWaveCnt) * (3.0f * m_fWaveCnt)
			+ m_fPbPos[0] * (1.0f - m_fWaveCnt) * 3.0f * m_fWaveCnt * m_fWaveCnt
			+ m_fEndPos[0] * m_fWaveCnt * m_fWaveCnt * m_fWaveCnt; // x座標移動
		m_pos[1] = m_fStartPos[1] * (1.0f - m_fWaveCnt) * (1.0f - m_fWaveCnt) * (1.0f - m_fWaveCnt)
			+ m_fPaPos[1] * (1.0f - m_fWaveCnt) * (1.0f - m_fWaveCnt) * (3.0f * m_fWaveCnt)
			+ m_fPbPos[1] * (1.0f - m_fWaveCnt) * 3.0f * m_fWaveCnt * m_fWaveCnt
			+ m_fEndPos[1] * m_fWaveCnt * m_fWaveCnt * m_fWaveCnt; // y座標移動
		if (m_pos[2] < -6.0f) // カメラが映らないまで近く
		{
			m_pos[2] = m_fStartZ_Pos; // Z座標 reset
			m_fWaveCnt = 0.0f;
			m_bReborn = true; // Reborn状態に
		} // 奥に戻してループ
#ifdef _DEBUG
		else m_pos[2] -= g_testZ_Speed; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~テスト用に奥から手前に Z座標移動
#endif
		if (!m_bReborn)
		{
			switch (m_nStrength) // 強度で X座標移動速度
			{
			case 0:
				m_fWaveCnt += 1.0f / (g_WaveX_Move / g_fParticleSpeedX_Normal); // 1 / (g_WaveX_Moveまで必須のフレイム数)
				break;
			case 1:
				m_fWaveCnt += 1.0f / (g_WaveX_Move / g_fParticleSpeedX_Strong); // 1 / (g_WaveX_Moveまで必須のフレイム数)
				break;
			case 2:
				m_fWaveCnt += 1.0f / (g_WaveX_Move / g_fParticleSpeedX_Weak); // 1 / (g_WaveX_Moveまで必須のフレイム数)
				break;
			default:
				break;
			}
		}
	}
}

void WindParticles::Draw()
{
	if (bReborn()) return;
	//変換行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);

	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale[0], m_scale[1], m_scale[2]);

	DirectX::XMMATRIX mat = S * T;

	//変換行列をGPUに渡すための前処理
	mat = DirectX::XMMatrixTranspose(mat); // 行列を転置する
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);

	//描画処理
	Geometory::SetWorld(fMat);
	Geometory::DrawBox();
}

void WindParticles::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

void WindParticles::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

bool WindParticles::bReborn()
{
	return m_bReborn;
}

void WindParticles::SetReborn(bool b)
{
	m_bReborn = b;
}

void WindParticles::ConstructorWindNormal() // 強度：普通
{
	if (m_bDirectionRight) // -------------------------------------------------------------------------- 右向き
	{
		m_fStartPos[0] = m_pos[0] * -1.0f; m_fStartPos[1] = m_pos[1]; m_fStartPos[2] = m_pos[2]; // ベジェ曲線の初期位置座標
		switch (m_nFrontBackPattern) // 3つに分ける
		{
		case 0: // 真ん中
			break;
		case 1: // 奥
			m_pos[2] += m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] -= g_fParticleX_Distance;
			m_fStartPos[0] -= g_fParticleX_Distance;
			break;
		case 2: // 手前
			m_pos[2] -= m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] += g_fParticleX_Distance;
			m_fStartPos[0] += g_fParticleX_Distance;
			break;
		default:
			break;
		}
		m_fPaPos[0] = m_fStartPos[0] + g_WaveX_Move * 0.9f;
		m_fPaPos[1] = m_fStartPos[1] + g_WaveY_Move_Normal;
		m_fPaPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pa
		m_fPbPos[0] = m_fStartPos[0] + g_WaveX_Move * 0.1f;
		m_fPbPos[1] = m_fStartPos[1] - g_WaveY_Move_Normal;
		m_fPbPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pb
		m_fEndPos[0] = m_fStartPos[0] + g_WaveX_Move;
		m_fEndPos[1] = m_fStartPos[1];
		m_fEndPos[2] = m_fStartPos[2]; // ベジェ曲線終点
	}
	else // ---------------------------------------------------------------------------------------- 左向き
	{
		m_fStartPos[0] = m_pos[0]; m_fStartPos[1] = m_pos[1]; m_fStartPos[2] = m_pos[2];
		switch (m_nFrontBackPattern) // 3つに分ける
		{
		case 0: // 真ん中
			break;
		case 1: // 奥
			m_pos[2] += m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] -= g_fParticleX_Distance;
			m_fStartPos[0] -= g_fParticleX_Distance;
			break;
		case 2: // 手前
			m_pos[2] -= m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] += g_fParticleX_Distance;
			m_fStartPos[0] += g_fParticleX_Distance;
			break;
		default:
			break;
		}
		m_fPaPos[0] = m_fStartPos[0] - g_WaveX_Move * 0.9f;
		m_fPaPos[1] = m_fStartPos[1] + g_WaveY_Move_Normal;
		m_fPaPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pa
		m_fPbPos[0] = m_fStartPos[0] - g_WaveX_Move * 0.1f;
		m_fPbPos[1] = m_fStartPos[1] - g_WaveY_Move_Normal;
		m_fPbPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pb
		m_fEndPos[0] = m_fStartPos[0] - g_WaveX_Move;
		m_fEndPos[1] = m_fStartPos[1];
		m_fEndPos[2] = m_fStartPos[2]; // ベジェ曲線終点
	}
}

void WindParticles::ConstructorWindStrong() // 強度：強
{
	if (m_bDirectionRight) // -------------------------------------------------------------------------- 右向き
	{
		m_fStartPos[0] = m_pos[0] * -1.0f; m_fStartPos[1] = m_pos[1]; m_fStartPos[2] = m_pos[2]; // ベジェ曲線の初期位置座標
		switch (m_nFrontBackPattern) // 3つに分ける
		{
		case 0: // 真ん中
			break;
		case 1: // 奥
			m_pos[2] += m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] -= g_fParticleX_Distance;
			m_fStartPos[0] -= g_fParticleX_Distance;
			break;
		case 2: // 手前
			m_pos[2] -= m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] += g_fParticleX_Distance;
			m_fStartPos[0] += g_fParticleX_Distance;
			break;
		default:
			break;
		}
		m_fPaPos[0] = m_fStartPos[0] + g_WaveX_Move * 1.0f;
		m_fPaPos[1] = m_fStartPos[1] + g_WaveY_Move_Strong;
		m_fPaPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pa
		m_fPbPos[0] = m_fStartPos[0] + g_WaveX_Move * 0.0f;
		m_fPbPos[1] = m_fStartPos[1] - g_WaveY_Move_Strong;
		m_fPbPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pb
		m_fEndPos[0] = m_fStartPos[0] + g_WaveX_Move;
		m_fEndPos[1] = m_fStartPos[1];
		m_fEndPos[2] = m_fStartPos[2]; // ベジェ曲線終点
	}
	else // ---------------------------------------------------------------------------------------- 左向き
	{
		m_fStartPos[0] = m_pos[0]; m_fStartPos[1] = m_pos[1]; m_fStartPos[2] = m_pos[2];
		switch (m_nFrontBackPattern) // 3つに分ける
		{
		case 0: // 真ん中
			break;
		case 1: // 奥
			m_pos[2] += m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] -= g_fParticleX_Distance;
			m_fStartPos[0] -= g_fParticleX_Distance;
			break;
		case 2: // 手前
			m_pos[2] -= m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] += g_fParticleX_Distance;
			m_fStartPos[0] += g_fParticleX_Distance;
			break;
		default:
			break;
		}
		m_fPaPos[0] = m_fStartPos[0] - g_WaveX_Move * 1.0f;
		m_fPaPos[1] = m_fStartPos[1] + g_WaveY_Move_Strong;
		m_fPaPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pa
		m_fPbPos[0] = m_fStartPos[0] - g_WaveX_Move * 0.0f;
		m_fPbPos[1] = m_fStartPos[1] - g_WaveY_Move_Strong;
		m_fPbPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pb
		m_fEndPos[0] = m_fStartPos[0] - g_WaveX_Move;
		m_fEndPos[1] = m_fStartPos[1];
		m_fEndPos[2] = m_fStartPos[2]; // ベジェ曲線終点
	}
}

void WindParticles::ConstructorWindWeak()
{
	if (m_bDirectionRight) // -------------------------------------------------------------------------- 右向き
	{
		m_fStartPos[0] = m_pos[0] * -1.0f; m_fStartPos[1] = m_pos[1]; m_fStartPos[2] = m_pos[2]; // ベジェ曲線の初期位置座標
		switch (m_nFrontBackPattern) // 3つに分ける
		{
		case 0: // 真ん中
			break;
		case 1: // 奥
			m_pos[2] += m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] -= g_fParticleX_Distance;
			m_fStartPos[0] -= g_fParticleX_Distance;
			break;
		case 2: // 手前
			m_pos[2] -= m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] += g_fParticleX_Distance;
			m_fStartPos[0] += g_fParticleX_Distance;
			break;
		default:
			break;
		}
		m_fPaPos[0] = m_fStartPos[0] + g_WaveX_Move * 0.4f;
		m_fPaPos[1] = m_fStartPos[1] - g_WaveY_Move_Weak;
		m_fPaPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pa
		m_fPbPos[0] = m_fStartPos[0] + g_WaveX_Move * 0.6f;
		m_fPbPos[1] = m_fStartPos[1] - g_WaveY_Move_Weak;
		m_fPbPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pb
		m_fEndPos[0] = m_fStartPos[0] + g_WaveX_Move;
		m_fEndPos[1] = m_fStartPos[1];
		m_fEndPos[2] = m_fStartPos[2]; // ベジェ曲線終点
	}
	else // ---------------------------------------------------------------------------------------- 左向き
	{
		m_fStartPos[0] = m_pos[0]; m_fStartPos[1] = m_pos[1]; m_fStartPos[2] = m_pos[2];
		switch (m_nFrontBackPattern) // 3つに分ける
		{
		case 0: // 真ん中
			break;
		case 1: // 奥
			m_pos[2] += m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] -= g_fParticleX_Distance;
			m_fStartPos[0] -= g_fParticleX_Distance;
			break;
		case 2: // 手前
			m_pos[2] -= m_fWindWidth;
			m_fStartPos[2] += m_fWindWidth;
			m_pos[0] += g_fParticleX_Distance;
			m_fStartPos[0] += g_fParticleX_Distance;
			break;
		default:
			break;
		}
		m_fPaPos[0] = m_fStartPos[0] - g_WaveX_Move * 0.4f;
		m_fPaPos[1] = m_fStartPos[1] - g_WaveY_Move_Weak;
		m_fPaPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pa
		m_fPbPos[0] = m_fStartPos[0] - g_WaveX_Move * 0.6f;
		m_fPbPos[1] = m_fStartPos[1] - g_WaveY_Move_Weak;
		m_fPbPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pb
		m_fEndPos[0] = m_fStartPos[0] - g_WaveX_Move;
		m_fEndPos[1] = m_fStartPos[1];
		m_fEndPos[2] = m_fStartPos[2]; // ベジェ曲線終点
	}
}

