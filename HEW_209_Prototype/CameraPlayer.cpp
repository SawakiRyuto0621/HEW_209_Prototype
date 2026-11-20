#include "CameraPlayer.h"
#include "Player.h"
#include "Input.h"
#include "Defines.h"


CameraPlayer::CameraPlayer()
    : m_radXZ(0.0f), m_radY(0.0f), m_radius(5.0f)
    , m_pPlayer(nullptr)
{
}

CameraPlayer::~CameraPlayer()
{
}

void CameraPlayer::Update()
{
    // プレイヤーの位置を注視点として設定 
    m_look = m_pPlayer->GetPos();

    //キー入力に応じたカメラの回転処理
    // 回り込みの処理
    constexpr float rotate = DirectX::XMConvertToRadians(90.0f / FPS);
    //if (IsKeyPress('W')) { m_radY += rotate; } // radY+
    //if (IsKeyPress('S')) { m_radY -= rotate; } // radY-
    //if (IsKeyPress('A')) { m_radXZ -= rotate; } // radXZ-
    //if (IsKeyPress('D')) { m_radXZ += rotate; } // radXZ+

    //メンバー変数の値に基づいて回り込むカメラの計算
        //  カメラ位置の計算
    const int CameraHeight = 3.0f;
    m_pos.x = cos(m_radY) * -sin(m_radXZ) * m_radius + m_look.x;
    m_pos.y = sin(m_radY) * m_radius + m_look.y + CameraHeight;
    m_pos.z = cos(m_radY) * -cos(m_radXZ) * m_radius + m_look.z;
}

void CameraPlayer::SetPlayer(Player* player)
{
    m_pPlayer = player;
}
