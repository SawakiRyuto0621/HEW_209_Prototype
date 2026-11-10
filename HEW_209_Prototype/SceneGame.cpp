#include "SceneGame.h"
#include "CameraDebug.h"
#include "Geometory.h"
#include "ShaderList.h"

SceneGame::SceneGame()
	:m_pPlayer(nullptr)
	,m_pCamera(nullptr)
	,m_pGround(nullptr)
	,m_pModel(nullptr)
{
	m_pGround = new Ground;
	m_pGround->SetPos(0.0f, 0.0f, 0.0f);
	m_pGround->SetScale(5.0f, 0.4f, 5.0f);

	m_pPlayer = new Player();
	m_pPlayer->SetPos(0.0f, 1.5f, 0.0f);
	m_pPlayer->SetScale(1.5f, 0.25f, 0.5f);

	m_pCamera = new CameraDebug();

	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/tree_forest.fbx", 1.0f, Model::None)) {
		MessageBox(NULL, "tree_forest.fbx", "error", MB_OK);
	}

	//深度テストの有効性
	SetDepthTest(DEPTH_ENABLE);
}

SceneGame::~SceneGame()
{
	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
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
	m_pCamera->Update();

}

void SceneGame::Draw()
{
	//仮置きしているボックスにカメラを設定
	Geometory::SetView(m_pCamera->GetViewMatrix());
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix());

	m_pGround->Draw();
	m_pPlayer->Draw();

	if (m_pModel) {
		//モデルを表示するためのワールド行列を計算
		DirectX::XMFLOAT4X4 fWorld;
		//DirectX::XMMATRIX world;
		//変換行列の計算
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
		DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(0.0f);
		DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(0.0f);
		DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(0.0f);
		DirectX::XMMATRIX R = Rx * Ry * Rz;
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
		DirectX::XMMATRIX world = S * R * T;

		DirectX::XMStoreFloat4x4(&fWorld, world);

		//シェーダーに必要なデータを設定
		ShaderList::SetWorld(fWorld);
		ShaderList::SetView(m_pCamera->GetViewMatrix());
		ShaderList::SetProjection(m_pCamera->GetProjectionMatrix());

		// モデルに使用する各種シェーダーを設定
		m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
		m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

		//メッシュ別にモデルを表示
		for (int i = 0; i < m_pModel->GetMeshNum(); ++i) {
			// モデルのメッシュを取得
			const Model::Mesh* mesh = m_pModel->GetMesh(i);

			//メッシュに割り当てられているマテリアルを取得
			Model::Material material = *m_pModel->GetMaterial(mesh->materialID);

			//シェーダーへマテリアルを設定
			ShaderList::SetMaterial(material);

			//モデルの描画（内部的に一括で行っていた描画処理を、メッシュごとの描画処理に変更）
			m_pModel->Draw(i);
		}


	}


}
