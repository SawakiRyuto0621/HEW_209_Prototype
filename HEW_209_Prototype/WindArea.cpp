#include "WindArea.h"
#include "geometory.h"
#include "Defines.h"

// ********************  開発履歴  ********************
// 2026/11/14  *****  陳  *****  クラス作成
// 2026/11/18  *****  陳  *****  同じ速度で動く boxを作成

constexpr float g_fAreaLength = METER(20.0f);

WindArea::WindArea(float posZ, float width)
	: m_pos{ 0.0f, 0.0f, posZ }
	, m_scale{ g_fAreaLength, 0.1f, width }
	, m_fAccelerateWithPlayer(1.0f)
{
}

WindArea::~WindArea()
{
}

void WindArea::Update()
{
	m_pos[2] -= g_testZ_Speed * m_fAccelerateWithPlayer;
}

void WindArea::Draw()
{
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

void WindArea::SetPos(float x, float y, float z)
{
}

void WindArea::SetScale(float x, float y, float z)
{
}

void WindArea::SetAccelerateWithPlayer(float acceleration)
{
	m_fAccelerateWithPlayer = acceleration;
}
