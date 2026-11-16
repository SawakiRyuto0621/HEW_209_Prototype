#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "Ground.h"
#include "Model.h"
#include "Tree.h"

class Stage;

class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void Update() final;
	void Draw() final;
	bool bInWind(); // Player Z座標が風の範囲内かチェック
	void WindtoPlayer();

private:
	Player* m_pPlayer; //プレイヤー
	Camera* m_pCamera;
	Ground* m_pGround; //地面オブジェクト
	Model* m_pModel;
	Stage* m_pStage;
	Tree* m_pTree; //木オブジェクト
};

#endif // __SCENE_GAME_H__