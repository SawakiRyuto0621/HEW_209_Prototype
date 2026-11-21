#include "Player.h"
#include "Geometory.h"
#include "Input.h"
#include "Defines.h"

Player::Player()
	: m_pos{0.0f, 0.0f,0.0f}
	, m_scale{1.0f, 1.0f, 1.0f}
	, m_angle(0.0f)
	, m_fSpeed {0.0f, 0.0f, 0.0f} // Playerの速度を取得(現在は主にX)
	, m_bTurn(false) // 左右旋回フラグ
	, m_bUpDown(false) // 上下フラグ
	, m_bBoost(false)  // 加速フラグ
	, m_bKeyPress(false)
{
}

Player::~Player()
{

}

void Player::Update()
{
	
	const float speed = METER(5.0f) / FPS;
	
	if (IsKeyPress('A') || IsKeyPress('D') || IsKeyPress('W') || IsKeyPress('S'))
	{ 
		/*if (!m_bBoost)
		{*/
			if (IsKeyPress('A')) // 左旋回
			{
				m_bTurn = true;
				// 移動制限まで移動
				if (m_pos[0] > METER(-5.5f)) { m_pos[0] -= speed; }
				// 旋回角度
				if (m_angle < DirectX::XMConvertToRadians(25.0f))
					m_angle += DirectX::XMConvertToRadians(1.0f);
				m_fSpeed.x = -speed;
			}
			else if (IsKeyPress('D')) // 右旋回
			{
				m_bTurn = true;
				// 移動制限まで移動
				if (m_pos[0] < METER(5.5f)) { m_pos[0] += speed; }
				// 旋回角度
				if (m_angle > DirectX::XMConvertToRadians(-25.0f))
					m_angle -= DirectX::XMConvertToRadians(1.0f);
				m_fSpeed.x = speed;
			}
			
			if (IsKeyPress('W'))
			{
				m_bUpDown = true;
				if (m_angle > DirectX::XMConvertToRadians(-25.0f))
					m_angle -= DirectX::XMConvertToRadians(1.0f);
				if (IsKeyPress('W') && IsKeyPress(VK_SPACE))
					if (m_pos[1] < METER(3.0f)) { m_pos[1] += speed; }

			}
			else if (IsKeyPress('S'))
			{
				m_bUpDown = true;
				if (m_angle < DirectX::XMConvertToRadians(25.0f))
					m_angle += DirectX::XMConvertToRadians(1.0f);
				if (IsKeyPress('S') && IsKeyPress(VK_CONTROL))
					if (m_pos[1] > METER(0.5f))
					{
						m_bBoost = true;
						m_pos[1] -= speed;
					}

			}

		//}
		
		
		m_bKeyPress = true;
	
	}
	else 
	{
		m_bTurn = false;
		m_bUpDown = false;
		m_bKeyPress = false;
		m_angle = 0.0f;
		m_fSpeed.x = 0.0f;
	}

	//if (IsKeyPress('W') || IsKeyPress('S'))
	//{
	//	m_bUpDown = true;
	//	if (IsKeyPress('W'))
	//	{
	//		if (m_angle > DirectX::XMConvertToRadians(25.0f))
	//			m_angle += DirectX::XMConvertToRadians(1.0f);
	//	}
	//	else if (IsKeyPress('S'))
	//	{
	//		if (m_angle > DirectX::XMConvertToRadians(-25.0f))
	//			m_angle -= DirectX::XMConvertToRadians(1.0f);
	//	}
	//}
	//else
	//{
	//	m_bUpDown = false;
	//	m_angle = 0.0f;
	//}
}

void Player::Draw()
{
	//変換行列の計算
	DirectX::XMMATRIX mat;
	
	if (m_bTurn || m_bUpDown)
	{
		if (m_bTurn)
		{
			DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(m_angle);
			DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);
			DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale[0], m_scale[1], m_scale[2]);
			mat = S * Z * T;
		}
		else if(m_bUpDown)
		{
			DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(m_angle);
			DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);
			DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale[0], m_scale[1], m_scale[2]);
			mat = S * X * T;
		}
	}
	else
	{
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale[0], m_scale[1], m_scale[2]);
		mat = S * T;
	}

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

DirectX::XMFLOAT3 Player::GetPos()
{
	DirectX::XMFLOAT3 playerPos = { m_pos[0], m_pos[1], m_pos[2] };
	return playerPos;
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

DirectX::XMFLOAT3 Player::GetPlayerSpeed() // Playerの速度を取得(現在は主にX)
{
	return m_fSpeed;
}

void Player::AddSpeed(float x, float y, float z) //速度変更
{
	float minSpeed = METER(20.0f * 1000) / (FPS * 60 * 60); //最低速度
	if (m_fSpeed.z + z * 2 >= minSpeed)
	{
		m_fSpeed.x += x;
		m_fSpeed.y += y;
		m_fSpeed.z += z;
	}
}
