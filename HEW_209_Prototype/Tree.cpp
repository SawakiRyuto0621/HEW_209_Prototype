// 木
// 林　11/16 作成
// 林　11/22 木のペア生成を作成

#include "Tree.h"
#include "ShaderList.h"
#include "Defines.h"

Tree::Tree()
	:m_pos{0.0f,0.0f,0.0f}
	,m_scale{1.0f,1.0f,1.0f}
	,m_pModel(nullptr)
{

	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/tree_forest.fbx", 1.0f, Model::None)) {
		MessageBox(NULL, "tree_forest.fbx", "error", MB_OK);
	}

}

Tree::~Tree()
{
  
	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}

}

void Tree::Update()
{

}

void Tree::Draw()
{
	// 変換行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale[0], m_scale[1], m_scale[2]);
	DirectX::XMMATRIX mat = S * T;

	// 変換行列をGPUに渡すための前処理
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;
	//matをfMatに変換
	DirectX::XMStoreFloat4x4(&fMat, mat);

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

void Tree::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

void Tree::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

DirectX::XMFLOAT3 Tree::GetPos()
{
	return DirectX::XMFLOAT3(
		m_pos[0],
		m_pos[1],
		m_pos[2]
	);
}

void Tree::CreateTreePair(std::vector<Tree*>& tree, float z, float distance)
{
	// 1本目の木
	Tree* tree1 = new Tree();

	tree1->SetScale(0.8f, 0.8f, 0.8f);
	tree1->SetPos(METER(distance), 0.0f, z);

	// 2本目の木
	Tree* tree2 = new Tree();

	tree2->SetScale(0.8f, 0.8f, 0.8f);
	tree2->SetPos(METER(-distance), 0.0f, z);

	// vectorに追加
	tree.push_back(tree1);
	tree.push_back(tree2);
}

