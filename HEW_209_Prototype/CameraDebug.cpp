#include "CameraDebug.h"
#include "Input.h"
#include "Defines.h"

CameraDebug::CameraDebug()
	:m_radXZ(0.0f), m_radY(0.0f), m_radius(2.0f)
	,m_pGoalCamera(nullptr)
{
	m_pGoalCamera = new GoalCamera();
}

CameraDebug::~CameraDebug()
{
	if (m_pGoalCamera)
	{
		delete m_pGoalCamera;
		m_pGoalCamera = nullptr;
	}
}

void CameraDebug::Update()
{
	// 確認用でJ-key
	// ゴールカメラ開始
	if (IsKeyPress('J') && !m_pGoalCamera->GetGoalflag())
	{
		m_pGoalCamera->Start(m_pos, m_look);
	}
	m_pGoalCamera->Update();

	if (m_pGoalCamera->GetGoalflag())
	{
		m_pos = m_pGoalCamera->GetPos();
		m_look = m_pGoalCamera->GetLook();
	}
	

	//直接数字で移動速度を設定するより、
	//1秒間の移動距離から1フレームの速度が計算できるとよい
	//const float speed = METER(5.0f) / FPS; //一秒間に5メートル動く

	////キー入力に合わせた注視点の移動距離
	//if (IsKeyPress(VK_UP)) { m_look.z += speed; }

	//if (IsKeyPress(VK_DOWN)) { m_look.z -= speed; }

	//if (IsKeyPress(VK_LEFT)) { m_look.x -= speed; }

	//if (IsKeyPress(VK_RIGHT)) { m_look.x += speed; }

	//if (IsKeyPress(VK_SHIFT)) { m_look.y += speed; }

	//if (IsKeyPress(VK_CONTROL)) { m_look.y -= speed; }

	////---カメラ位置の移動
	////回り込みの処理
	//const float rotate = DirectX::XMConvertToRadians(180.0f) / FPS;
	//if (IsKeyPress('A')) { m_radXZ += rotate; }
	//if (IsKeyPress('D')) { m_radXZ -= rotate; }
	//if (IsKeyPress('W')) { m_radY += rotate; }
	//if (IsKeyPress('S')) { m_radY -= rotate; }

	////カメラの距離を変える処理
	//const float radiusSpeed = METER(1.0f) / FPS;
	//if (IsKeyPress('Q')) { m_radius += radiusSpeed; }
	//if (IsKeyPress('E')) { m_radius -= radiusSpeed; }

	////カメラ位置の計算
	//m_pos.x = cosf(m_radY) * -sinf(m_radXZ) * m_radius + m_look.x;
	//m_pos.y = sinf(m_radY) * m_radius + m_look.y;
	//m_pos.z = cosf(m_radY) * -cosf(m_radXZ) * m_radius + m_look.z;

}