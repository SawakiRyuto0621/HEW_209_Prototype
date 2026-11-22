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
class UI;

class SceneGame : public Scene
{

private:
	
	Player* m_pPlayer; //プレイヤー
	Camera* m_pCamera;
	Ground* m_pGround; //地面オブジェクト
	Model* m_pModel;
	Stage* m_pStage; // ステージ
	std::vector<Tree*> m_pTree; //木オブジェクトを管理するコンテナ
	Prey* m_pPrey; //獲物
	UI* m_pUI;

public:
	SceneGame();
	~SceneGame();
	void Update() final;
	void Draw() final;
	bool bInWind(); // Player Z座標が風の範囲内かチェック
	void WindtoPlayer(); // 加速で Zスクロールが加速
	void TreeAcc();	//木の加速処理


};

#endif // __SCENE_GAME_H__