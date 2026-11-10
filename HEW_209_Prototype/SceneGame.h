#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "Ground.h"
#include "Model.h"

class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void Update() final;
	void Draw() final;

private:
	Player* m_pPlayer; //プレイヤー
	Camera* m_pCamera;
	Ground* m_pGround; //地面オブジェクト
	Model* m_pModel;
};

#endif // __SCENE_GAME_H__