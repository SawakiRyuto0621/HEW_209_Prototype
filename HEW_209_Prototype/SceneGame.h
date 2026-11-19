#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "Ground.h"
#include "Model.h"
#include "Tree.h"
#include "Prey.h"
#include "DirectXMath.h"

class Stage;

class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void Update() final;
	void Draw() final;
	bool bInWind(); // Player Z座標が風の範囲内かチェック
	void WindtoPlayer(); // 加速で Zスクロールが加速

private:
	static const int TREE_NUM = 2;	// 木の管理（必要に応じて本数を変更可）

	Player* m_pPlayer; //プレイヤー
	Camera* m_pCamera;
	Ground* m_pGround; //地面オブジェクト
	Model* m_pModel;
	Stage* m_pStage; // ステージ
	Tree* m_pTree[TREE_NUM]; //木オブジェクト 複数の木をまとめて管理するための配列
	Prey* m_pPrey; //獲物
};

#endif // __SCENE_GAME_H__