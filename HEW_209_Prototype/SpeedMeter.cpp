#include "SpeedMeter.h"
#include "Model.h"
#include "DirectXTex/TextureLoad.h"

// ********************  開発履歴  ********************
// 2026/11/22  *****  陳  *****  UIで Speed Meterが表示される、速度も反映(Stageの仮速度)(最大200km/h)

constexpr int g_DigitSpeed = 3; // 数字の数（配列の要素数）
constexpr int g_AnimScoreSplitX = 5; // 画像の分割数(横)
constexpr int g_AnimScoreSplitY = 2; // 画像の分割数(縦)
constexpr float g_posX = 0.5f;
constexpr float g_posY = -0.7f;

struct TSPEED {
	DirectX::XMFLOAT2 m_Numberpos;
	DirectX::XMFLOAT2 m_posTexCoord;
	DirectX::XMFLOAT2 m_sizeTexCoord;
	bool m_use;
	int m_currentAnimNo;
};

//**********グローバル変数**********
TSPEED			g_aSpeedDigits[g_DigitSpeed]; // Speed構造体配列

SpeedMeter::SpeedMeter()
	: m_pTexture(nullptr)
	, m_pNumberBuf(nullptr)
	, m_pNumberTex(nullptr)
	, m_pos{ g_posX, g_posY }
	, m_nSpeed(123)
	, m_bSpeedAdded(false)
{
	m_pTexture = new Texture();
	//m_pTexture->Create("Numbers.png");
	if (FAILED(m_pTexture->Create("Assets/Model/Numbers.png")))
	{
		MessageBox(NULL, "SpeedMeter.cpp, Texture Load, Numbers.png", "Error", MB_OK);
	}
	float basePosX = m_pos.x; float basePosY = m_pos.y;
	for (int i = 0; i < g_DigitSpeed; ++i)
	{
		g_aSpeedDigits[i].m_Numberpos.x = basePosX + 0.2f * i /*+ g_SpeedSizeX * i*/;
		g_aSpeedDigits[i].m_Numberpos.y = basePosY;


		g_aSpeedDigits[i].m_posTexCoord.x = 0.0f;
		g_aSpeedDigits[i].m_posTexCoord.y = 0.0f;

		g_aSpeedDigits[i].m_sizeTexCoord.x = 1.0f / g_AnimScoreSplitX;
		g_aSpeedDigits[i].m_sizeTexCoord.y = 1.0f / g_AnimScoreSplitY;

		g_aSpeedDigits[i].m_use = true;
		g_aSpeedDigits[i].m_currentAnimNo = 0;
	}
}


SpeedMeter::~SpeedMeter()
{
	if (m_pTexture) { delete m_pTexture; m_pTexture = nullptr; }
}

void SpeedMeter::Update()
{
	UpdateSpeedTexcoord();
}

void SpeedMeter::Draw()
{
	for (int i = 0; i < g_DigitSpeed; i++)
	{
		// 未使用のものは処理をしない
		if (!g_aSpeedDigits[i].m_use)
		{
			continue;
		}
		Sprite::SetSize(DirectX::XMFLOAT2(0.2f, 0.5f)); // Size
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f / g_AnimScoreSplitX, 1.0f / g_AnimScoreSplitY));
		Sprite::SetUVPos(DirectX::XMFLOAT2(g_aSpeedDigits[i].m_posTexCoord.x, g_aSpeedDigits[i].m_posTexCoord.y));
		//  変換行列の計算
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(g_aSpeedDigits[i].m_Numberpos.x, g_aSpeedDigits[i].m_Numberpos.y, 0.0f);
		// 変換行列をGPUに渡すための前処理 
		T = DirectX::XMMatrixTranspose(T); // 転置
		DirectX::XMFLOAT4X4 fMat;
		DirectX::XMStoreFloat4x4(&fMat, T);
		Sprite::SetWorld(fMat);

		Sprite::SetTexture(m_pTexture);
		Sprite::Draw();
	}
}

void SpeedMeter::SetSpeed(int speed)
{
	m_nSpeed = speed;

	if (m_nSpeed > 200) m_nSpeed = 200;
	UpdateSpeedTexcoord();
	m_bSpeedAdded = true;
}

void SpeedMeter::UpdateSpeedTexcoord()
{
	int tmp = m_nSpeed;

	for (int i = g_DigitSpeed - 1; 0 <= i; --i) // i = 4, 3...0
	{
		// tmpに入った値の下１桁を取得
		g_aSpeedDigits[i].m_currentAnimNo = tmp % 10; // 12345 % 10 = 5

		// テクスチャ座標更新
		g_aSpeedDigits[i].m_posTexCoord.x =
			g_aSpeedDigits[i].m_sizeTexCoord.x *
			(g_aSpeedDigits[i].m_currentAnimNo % g_AnimScoreSplitX); // e.g. 0.2 * 5 % 5 = 0, 0.2 * 1 % 5 = 1
		g_aSpeedDigits[i].m_posTexCoord.y =								// 0.2 * 0, 1, 2, 3, 4, 0, 1... 
			g_aSpeedDigits[i].m_sizeTexCoord.y *
			(g_aSpeedDigits[i].m_currentAnimNo / g_AnimScoreSplitX); // e.g. 0.2 * 5 / 5 = 0.2, 0.2 * 1 / 5 = 0;
		// 0.2 * 0, 0, 0, 0, 0, 1, 1...

		// 桁を１つ落とす
		// 例[12345]ー＞[1234]下１桁を
		// 10で割った余りを求めることで取得するため
		tmp /= 10;
	}
}
