#include "Ground.h"
//#include <DirectXMath.h>
#include "Geometory.h"
#include "ShaderList.h"

Ground::Ground()
	:m_pos{ 0.0f, 0.0f, 0.0f },
	m_scale{ 1.0f, 1.0f, 1.0f }
{
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/tileSmall_forest.fbx", 1.0f, Model::None)) {
		MessageBox(NULL, "tileSmall_forest.fbx", "error", MB_OK);
	}
}

Ground::~Ground()
{
	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}
}

void Ground::Update()
{

}

void Ground::Draw()
{
	//変換行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);

	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale[0], m_scale[1], m_scale[2]);

	DirectX::XMMATRIX mat = S * T;

	//変換行列をGPUに渡すための前処理
	mat = DirectX::XMMatrixTranspose(mat); // 行列を転置する
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);

	////描画処理
	//Geometory::SetWorld(fMat);
	//Geometory::DrawBox();
	//描画処理
	if (m_pModel)
	{
		// モデルを表示するためのワールド行列を計算 

		ShaderList::SetWorld(fMat);

		// モデルに使用する各種シェーダーを設定 
		m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
		m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

		// メッシュ別にモデルを表示 
		for (int i = 0; i < m_pModel->GetMeshNum(); ++i)
		{
			// モデルのメッシュを取得 
			const Model::Mesh* mesh = m_pModel->GetMesh(i);

			// メッシュに割り当てられているマテリアルを取得 
			Model::Material material = *m_pModel->GetMaterial(mesh->materialID);

			// シェーダーへマテリアルを設定 
			ShaderList::SetMaterial(material);

			// モデルの描画(内部的に一括で行っていた描画処理を、メッシュごとの描画処理に変更) 
			m_pModel->Draw(i);
		}
	}

}

//座標の設定
void Ground::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

//拡大率の設定
void Ground::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}


