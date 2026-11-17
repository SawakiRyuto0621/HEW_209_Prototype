// 木
// 林　11/16
#include "Tree.h"
#include "ShaderList.h"
#include "Geometory.h"
#include "CameraDebug.h"

Tree::Tree()
	:m_pos{0.0f,0.0f,0.0f}
	,m_scale{1.0f,1.0f,1.0f}
	,m_pModel(nullptr)
    ,m_pCamera(nullptr)
{
    m_pCamera = new CameraDebug();

	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/tree_forest.fbx", 1.0f, Model::None)) {
		MessageBox(NULL, "tree_forest.fbx", "error", MB_OK);
	}

}

Tree::~Tree()
{
    if (m_pCamera) {
        delete m_pCamera;
        m_pCamera = nullptr;
    }

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
    if (!m_pModel) return;

    // ワールド行列の計算
    DirectX::XMMATRIX T =
        DirectX::XMMatrixTranslation(
            m_pos[0],
            m_pos[1],
            m_pos[2]
        );

    DirectX::XMMATRIX R =
        DirectX::XMMatrixRotationY(0.0f);

    DirectX::XMMATRIX S =
        DirectX::XMMatrixScaling(
            m_scale[0],
            m_scale[1],
            m_scale[2]);

    DirectX::XMMATRIX world = S * R * T;

    // 転置
    world = DirectX::XMMatrixTranspose(world);

    DirectX::XMFLOAT4X4 fWorld;
    DirectX::XMStoreFloat4x4(&fWorld, world);

    // ワールド行列を設定
    ShaderList::SetWorld(fWorld);
    ShaderList::SetView(m_pCamera->GetViewMatrix());
    ShaderList::SetProjection(m_pCamera->GetProjectionMatrix());

    // シェーダー設定
    m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
    m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

    // メッシュごとに描画
    for (int i = 0; i < m_pModel->GetMeshNum(); ++i)
    {
        const Model::Mesh* mesh = m_pModel->GetMesh(i);

        Model::Material material = *m_pModel->GetMaterial(mesh->materialID);

        ShaderList::SetMaterial(material);

        m_pModel->Draw(i);
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

