#include "GoalCamera.h"
#include "Defines.h"
#include "Input.h"

GoalCamera::GoalCamera()
	:m_radXZ(0.0f), m_radY(0.0f), m_radius(2.0f)
    ,m_startPos(0.0f, 0.0f, 0.0f),m_startLook(0.0f, 0.0f, 0.0f)
    ,m_goalFlag(false)
{
}

GoalCamera::~GoalCamera()
{
}

void GoalCamera::Update()
{
    if (!m_goalFlag)
        return;

    // ゴールカメラ停止
    if (IsKeyTrigger('K'))
    {
        Stop();

    }

    // 回り込みの処理
    constexpr float rotate = DirectX::XMConvertToRadians(180.0f) / (2.0f * FPS);
    // 動く距離
    constexpr float moveSpeed = METER(4.0f) / (1.0f * FPS);
    constexpr float upSpeed = METER(2.0f) / (1.0f * FPS);

    float moveMeter = METER(4.0f);
    // ズーム距離
    constexpr float zoomSpeed = METER(3.0f) / (0.5f * FPS);

    // カメラが右斜め前に動いて、近づく
    if (m_look.x < moveMeter && m_look.z < moveMeter)
    {
        m_look.x += moveSpeed;
        m_look.y += upSpeed;
        m_look.z += moveSpeed;
        
    }
    else
    {
        if (m_radius > 3.0f)
        {  
            m_radius -= zoomSpeed;
        }  
    }
  
   
    //獲物との距離で判定（今後実装
    if(m_radXZ > DirectX::XMConvertToRadians(-90.0f))
    m_radXZ -= rotate;
 
    //カメラ位置の計算
    m_pos.x = cosf(m_radY) * -sinf(m_radXZ) * m_radius + m_look.x;
    m_pos.y = sinf(m_radY) * m_radius + m_look.y;
    m_pos.z = cosf(m_radY) * -cosf(m_radXZ) * m_radius + m_look.z;
	
}


void GoalCamera::Start(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 look)
{
    // 元の位置と注視点を保管
    m_startPos = pos;
    m_startLook = look;

    // 現在のカメラ位置と注視点を受け取る
    m_pos = pos;
    m_look = look;
    // カメラの位置から角度と距離を計算
    float x = m_pos.x - m_look.x;
    float y = m_pos.y - m_look.y;
    float z = m_pos.z - m_look.z;
    
    m_radius = sqrtf(x * x + y * y + z * z); // カメラと注視点の距離計算（三平方
    m_radXZ = 0.0f;
    m_radY = asinf(y / m_radius); // 上下方向の角度計算

    m_goalFlag = true;
}

void GoalCamera::Stop()
{
    // 演出終了
    m_goalFlag = false;

    // 元のカメラ位置に戻す
    m_pos = m_startPos;
    m_look = m_startLook;

}

void GoalCamera::MoveGoalCamera()
{
    
}

bool GoalCamera::GetGoalflag()
{
    return m_goalFlag;
}



