#include "Player.h"
#include "Geometory.h"
#include "Input.h"
#include "Defines.h"

Player::Player()
	:m_pos{0.0f, 0.0f,0.0f}
	,m_scale{1.0f, 1.0f, 1.0f}
	, m_fSpeed {0.0f, 0.0f, 0.0f}
	, m_bKeyPress(false)
{
}

Player::~Player()
{

}

void Player::Update()
{
	const float speed = METER(5.0f) / FPS;
	if (IsKeyPress('A')) { m_pos[0] -= speed; }
	if (IsKeyPress('D')) { m_pos[0] += speed; }

	if (IsKeyPress(VK_LEFT) || IsKeyPress(VK_RIGHT))
	{
		if (IsKeyPress(VK_LEFT)) { m_fSpeed.x = speed; }
		if (IsKeyPress(VK_RIGHT)) { m_fSpeed.x = -speed; }
		m_bKeyPress = true;
	}
	else
	{
		m_fSpeed.x = 0;
		m_bKeyPress = false;
	}
}

void Player::Draw()
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

void Player::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

float Player::GetPosZ()
{
	return m_pos[2];
}

void Player::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

bool Player::GetKeyPress()
{
	return m_bKeyPress;
}

DirectX::XMFLOAT3 Player::GetPlayerSpeed()
{
	return m_fSpeed;
}
