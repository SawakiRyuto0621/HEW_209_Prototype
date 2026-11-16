#include "GoalCamera.h"
#include "Defines.h"

GoalCamera::GoalCamera()
	:m_radXZ(0.0f), m_radY(0.0f), m_radius(2.0f)
{
}

GoalCamera::~GoalCamera()
{
}

void GoalCamera::Update()
{
    //獲物との距離で判定（今後実装
    if (0) {
		//---カメラ位置の移動
		constexpr float rotate = DirectX::XMConvertToRadians(180.0f) / FPS; 



        //カメラ位置の計算
        m_pos.x = cosf(m_radY) * -sinf(m_radXZ) * m_radius + m_look.x;
        m_pos.y = sinf(m_radY) * m_radius + m_look.y;
        m_pos.z = cosf(m_radY) * -cosf(m_radXZ) * m_radius + m_look.z;

    }

	
}

