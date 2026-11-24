#include "SceneGame.h"
#include "CameraDebug.h"
#include "Geometory.h"
#include "ShaderList.h"
#include "Stage.h"
#include "DirectXMath.h"
#include "CameraPlayer.h"
#include "Defines.h"
#include "UI.h"

// ********************  開発履歴  ********************
// 2026/11/16  *****  陳  *****  風の情報取得、Playerの Z座標が範囲内かチェックする関数を作成
// 2026/11/19  *****  陳  *****  風で Z軸スクロール加速(テスト待ち)
// 2026/11/20  *****  林  *****  木に近づいた時の加速処理(テスト待ち）
// 2026/11/22  *****  林  *****  木の処理をコンテナでの管理に変更
// 2026/11/22  *****  陳  *****  UIで Speed Meterが表示される、速度も反映(Stageの仮速度)(最大200km/h)

constexpr float AddSpeedWind = METER(0.5f) * 1000 / (FPS * 60 * 60);
constexpr float DevideSpeedWind = METER(-0.5f) * 1000 / (FPS * 60 * 60);
constexpr float TreeBoostSpeed = 10.0f * 1000.0f / (FPS * 60 * 60);
bool m_bTreeBoost;

SceneGame::SceneGame()
	: m_pPlayer(nullptr)
	, m_pCamera(nullptr)
	, m_pGround(nullptr)
	, m_pModel(nullptr)
	, m_pStage(nullptr)
	, m_pPrey(nullptr)
	, m_pUI(nullptr)
{
	m_pGround = new Ground;
	m_pGround->SetPos(0.0f, -0.4f, 23.0f);
	m_pGround->SetScale(13.0f, 0.5f, 50.0f);

	m_pCamera = new CameraDebug();
	CameraPlayer* pCamera = new CameraPlayer();

	m_pPlayer = new Player();
	m_pPlayer->SetPos(0.0f, 1.5f, 0.0f);
	m_pPlayer->SetScale(1.5f, 0.25f, 0.5f);

	// カメラにプレイヤーを設定（プレイヤーの作成後に呼び出し） 
	pCamera->SetPlayer(m_pPlayer);
	// カメラの情報をメンバー変数に記録 
	m_pCamera = pCamera; // Camera クラスに格納するためCameraPlayerクラスではなくなる 

	m_pStage = new Stage();

	// 木のオブジェクト
	/*for (int i = 0; i < TreeNum; ++i) {
		Tree* tree = new Tree();
		tree->SetScale(0.8f, 0.8f, 0.8f);
		m_pTree.push_back(tree);
	}*/
	// 木のポジション決め（CreateTreePair(m_pTree,位置,始点,間隔))
	//１
	Tree::CreateTreePair(m_pTree, 3.8f, -5.0f, 2.5f);
	//２
	Tree::CreateTreePair(m_pTree, 8.8f, 2.0f, 1.8f);

	// 獲物オブジェクト
	m_pPrey = new Prey();
	m_pPrey->SetPos(0.0f, 3.0f, 0.0f);
	m_pPrey->SetScale(0.5f, 0.25f, 0.5f);

	m_pUI = new UI();

	//深度テストの有効性
	SetDepthTest(DEPTH_ENABLE);
}

SceneGame::~SceneGame()
{
	if (m_pPrey) {
		delete m_pPrey;
		m_pPrey = nullptr;
	}

	//for (int i = 0; i < m_pTree.size(); ++i) {
	//	if (m_pTree[i]) {
	//		delete m_pTree[i];
	//		m_pTree[i] = nullptr;
	//	}
	//	m_pTree.clear();
	//}

	if (m_pUI) { delete m_pUI; m_pUI = nullptr; }
	//木のオブジェクトを削除
	for (Tree* tree : m_pTree)
	{
		delete tree;
	}
		m_pTree.clear();
	
	if (m_pStage) {
		delete m_pStage;
		m_pStage = nullptr;
	}

	if (m_pCamera) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pPlayer) {
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pGround) {
		delete m_pGround;
		m_pGround = nullptr;
	}
}

void SceneGame::Update()
{
	m_pGround->Update();
	m_pPlayer->Update();
	WindtoPlayer(); // 風で加速の判定
	m_pCamera->Update();
	m_pStage->Update();
	for (Tree* tree : m_pTree) 
	{
		tree->Update();
	}
	TreeAcc(); // 木の間で加速
	m_pPrey->Update();
	float speedStage = abs(m_pStage->GetSpeedZ() / 1000 * (FPS * 60 * 60));
	m_pUI->SetSpeed(speedStage);
	m_pUI->Update();

}

void SceneGame::Draw()
{
	//仮置きしているボックスにカメラを設定
	Geometory::SetView(m_pCamera->GetViewMatrix());
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix());

	//仮置き以外にカメラを設定
	ShaderList::SetView(m_pCamera->GetViewMatrix());
	ShaderList::SetProjection(m_pCamera->GetProjectionMatrix());

	m_pGround->Draw();
	m_pPlayer->Draw();
	m_pStage->Draw();
	for (Tree* tree : m_pTree) 
	{
		tree->Draw();
	}
	m_pPrey->Draw();

	// UI用に2D設定切り替え
	ShaderList::SetView(m_pCamera->GetViewMatrix2D());
	ShaderList::SetProjection(m_pCamera->GetProjectionMatrix2D());
	//
	m_pUI->Draw();

}

bool SceneGame::bInWind() // Player Z座標が風の範囲内かチェック
{
	float WindPosZ = m_pStage->GetWindPosZ(); // 風の中心 Z座標
	float PlayerPosZ = m_pPlayer->GetPosZ(); // Playerの Z座標
	float WindWidth = m_pStage->GetWindWidth(); // 風の幅
	if (PlayerPosZ <= WindPosZ + WindWidth / 2.0f && PlayerPosZ >= WindPosZ - WindWidth / 2.0f) // 風の範囲内
	{
		return true;
	}
	return false;
}

void SceneGame::WindtoPlayer() // 加速で Zスクロールが加速
{
	if (!bInWind()) return; // 風の範囲外
	if (!m_pPlayer->GetKeyPress()) return; // キーを押していない
	DirectX::XMFLOAT3 playerSpeed = m_pPlayer->GetPlayerSpeed(); // 速度取得 (現在は主にX)
	if (m_pStage->GetWindDirectionRight()) // 風が右向き
	{
		if (playerSpeed.x > 0) // 右旋回
		{
			int windStrength = m_pStage->GetWindStrength();
			switch (windStrength)
			{
			case 0:
				m_pStage->AddSpeed(0.0f, 0.0f, AddSpeedWind);
				break;
			case 1:
				m_pStage->AddSpeed(0.0f, 0.0f, AddSpeedWind);
				break;
			case 2:
				m_pStage->AddSpeed(0.0f, 0.0f, AddSpeedWind);
				break;
			}
		}
		else // 左旋回
		{
			int windStrength = m_pStage->GetWindStrength();
			switch (windStrength)
			{
			case 0:
				m_pStage->AddSpeed(0.0f, 0.0f, DevideSpeedWind);
				break;
			case 1:
				m_pStage->AddSpeed(0.0f, 0.0f, DevideSpeedWind);
				break;
			case 2:
				m_pStage->AddSpeed(0.0f, 0.0f, DevideSpeedWind);
				break;
			}
		}
	}
	else if(!m_pStage->GetWindDirectionRight())// 風が左向き
	{
		if (playerSpeed.x < 0) // 左旋回
		{
			int windStrength = m_pStage->GetWindStrength();
			switch (windStrength)
			{
			case 0:
				m_pStage->AddSpeed(0.0f, 0.0f, AddSpeedWind);
				break;
			case 1:
				m_pStage->AddSpeed(0.0f, 0.0f, AddSpeedWind);
				break;
			case 2:
				m_pStage->AddSpeed(0.0f, 0.0f, AddSpeedWind);
				break;
			}
		}
		if (playerSpeed.x > 0) // 右旋回
		{
			int windStrength = m_pStage->GetWindStrength();
			switch (windStrength)
			{
			case 0:
				m_pStage->AddSpeed(0.0f, 0.0f, DevideSpeedWind);
				break;
			case 1:
				m_pStage->AddSpeed(0.0f, 0.0f, DevideSpeedWind);
				break;
			case 2:
				m_pStage->AddSpeed(0.0f, 0.0f, DevideSpeedWind);
				break;
			}
		}
	}
}

void SceneGame::TreeAcc()
{
	// Playerの現在位置を取得
	DirectX::XMFLOAT3 player = m_pPlayer->GetPos();

	// 2組の木を順番に調べる
	for (int i = 0; i < m_pTree.size() / 2; i++)
	{
		// 1組目なら0番と1番
    	// 2組目なら2番と3番
		int index = i * 2;

		// 木の位置を取得
		DirectX::XMFLOAT3 tree1 = m_pTree[index]->GetPos();
		DirectX::XMFLOAT3 tree2 = m_pTree[index + 1]->GetPos();

		// 木の間の範囲
		float minX = min(tree1.x, tree2.x);
		float maxX = max(tree1.x, tree2.x);

		// 木の間にいるか
		bool between =
			player.x > minX &&
			player.x < maxX;

		// 木のZ座標付近にいるか
		bool nearTree =
			player.z >= tree1.z - METER(0.5f) &&
			player.z <= tree1.z + METER(0.5f);

		// 両方の条件を満たしたら加速
		if (between && nearTree)
		{
			if (!m_bTreeBoost)
			{
				m_pPlayer->AddSpeed(0.0f, 0.0f, TreeBoostSpeed);
				m_bTreeBoost = true;
			}
		}
		else
		{
			m_bTreeBoost = false;
		}
	}
}

