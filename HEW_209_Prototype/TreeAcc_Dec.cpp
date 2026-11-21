#include "TreeAcc_Dec.h"

TreeAcc_Dec::TreeAcc_Dec(Tree* Tree,Player* Player)
	:m_pPlayer(Player)
	,m_pTree(Tree)
{

}

TreeAcc_Dec::~TreeAcc_Dec()
{
	if (m_pPlayer) {
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pTree) {
		delete m_pTree;
		m_pTree = nullptr;
	}
}

void TreeAcc_Dec::Update()
{

}