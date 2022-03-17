#pragma once
#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Field.h"
#include "Store.h"
#include "Inven.h"

class CMainGame
{
public:
	void	Initialize(void);
	void	Update(void);
	void	Release(void);

public:
	CMainGame();
	~CMainGame();

private:
	void Save_Data(void);

private:
	CObj* m_pPlayer;
	CField* m_pField;
	CStore* m_pStore;
	CInven* m_pInven;
};

