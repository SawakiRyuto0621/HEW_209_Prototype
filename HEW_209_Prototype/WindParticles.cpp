#include "WindParticles.h"
#include "Geometory.h"
#include "Defines.h"

constexpr float g_fParticleSpeedX = METER(5.0f) / FPS; // ****** 一旦x座標移動速度の設定(1フレイムの移動量)

WindParticles::WindParticles(float posZ, bool directionRight, int pattern)
	: m_pos{ 5.0f, 1.5f, posZ} // ***** 初期位置座標を調整
	, m_scale{ 0.2f, 0.2f, 0.2f }
	, m_fWaveCnt(0.0f) // ベジェ曲線用カウント
	, m_bDirectionRight(directionRight)
	, m_bReborn(false)
{
	if (m_bDirectionRight) // --------------------------------------------- 右向き
	{
		m_fStartPos[0] = m_pos[0] * -1.0f; m_fStartPos[1] = m_pos[1]; m_fStartPos[2] = m_pos[2]; // ベジェ曲線の初期位置座標
		switch (pattern) // 3つに分ける
		{
		case 0: // 真ん中
			break;
		case 1: // 奥
			m_pos[2] += 0.3f;
			m_fStartPos[2] += 0.3f;
			break;
		case 2: // 手前
			m_pos[2] -= 0.3f;
			m_fStartPos[2] += 0.3f;
			break;
		}
		// ********** 一旦10m X座標移動, 3m 上下Y座標移動
		m_fPaPos[0] = m_fStartPos[0] + 10.0f * 0.9f;
		m_fPaPos[1] = m_fStartPos[1] + 3.0f * 2 * 0.75f;
		m_fPaPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pa
		m_fPbPos[0] = m_fStartPos[0] + 10.0f * 0.1f;
		m_fPbPos[1] = m_fStartPos[1] - 3.0f * 2 * 0.25f;
		m_fPbPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pb
		m_fEndPos[0] = m_fStartPos[0] + 10.0f;
		m_fEndPos[1] = m_fStartPos[1];
		m_fEndPos[2] = m_fStartPos[2]; // ベジェ曲線終点
	}
	else // --------------------------------------------------------------- 左向き
	{
		m_fStartPos[0] = m_pos[0]; m_fStartPos[1] = m_pos[1]; m_fStartPos[2] = m_pos[2];
		switch (pattern) // 3つに分ける
		{
		case 0: // 真ん中
			break;
		case 1: // 奥
			m_pos[2] += 0.3f;
			m_fStartPos[2] += 0.3f;
			break;
		case 2: // 手前
			m_pos[2] -= 0.3f;
			m_fStartPos[2] += 0.3f;
			break;
		}
		// ********** 一旦10m X座標移動, 3m 上下Y座標移動
		m_fPaPos[0] = m_fStartPos[0] - 10.0f * 0.9f;
		m_fPaPos[1] = m_fStartPos[1] + 3.0f * 2 * 0.75f;
		m_fPaPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pa
		m_fPbPos[0] = m_fStartPos[0] - 10.0f * 0.1f;
		m_fPbPos[1] = m_fStartPos[1] - 3.0f * 2 * 0.25f;
		m_fPbPos[2] = m_fStartPos[2]; // ベジェ曲線制御点 Pb
		m_fEndPos[0] = m_fStartPos[0] - 10.0f;
		m_fEndPos[1] = m_fStartPos[1];
		m_fEndPos[2] = m_fStartPos[2]; // ベジェ曲線終点
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
		if (m_pos[2] < -6.0f)
		{
			m_pos[2] = 5.0f;
			m_fWaveCnt = 0.0f;
			m_bReborn = true;
		} // 奥に戻してループ
#ifdef _DEBUG
		else m_pos[2] -= 0.02f; // テスト用に奥から手前に Z座標移動
#endif
		if (!m_bReborn)
		m_fWaveCnt += 1.0f / (METER(10.0f) / g_fParticleSpeedX); // 1 / (10mまで必須のフレイム数)
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
