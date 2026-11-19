#pragma once
#include "Model.h"

class Ground {
private:
	float m_pos[3];    //座標
	float m_scale[3];  //拡大率

	Model* m_pModel;

public:
	Ground();
	~Ground();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//座標の設定
	void SetPos(float x, float y, float z);

	//拡大率の設定
	void SetScale(float x, float y, float z);
};
