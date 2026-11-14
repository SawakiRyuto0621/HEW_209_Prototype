#include "WindParticles.h"
#include "Geometory.h"

WindParticles::WindParticles()
	: m_pos{ 0.0f, 0.0f, 0.0f }
	, m_scale{ 1.0f, 1.0f, 1.0f }
{
}

WindParticles::~WindParticles()
{
}

void WindParticles::Update()
{

}

void WindParticles::Draw()
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
