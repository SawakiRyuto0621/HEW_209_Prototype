#pragma once
#include "Player.h"
#include "Tree.h"
#include "Stage.h"

class TreeAcc_Dec
{
private:
	Player* m_pPlayer;
	Tree* m_pTree;

	float m_accDistance;
	float m_accSpeed;
	float m_decSpeed;

public:

	TreeAcc_Dec(Tree* Tree, Player* Player);
	~TreeAcc_Dec();
	void Update();

};
