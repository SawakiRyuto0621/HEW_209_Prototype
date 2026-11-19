//–Ø
#pragma once
#include "Model.h"

class Tree
{
private:
	float m_pos[3];
	float m_scale[3];

	Model* m_pModel;

public:
	Tree();
	~Tree();
	void Update();
	void Draw();

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);

	
};