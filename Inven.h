#pragma once
#include "Player.h"
#include "Item.h"

class CInven
{
public:
	CInven();
	~CInven();

public:
	void Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	// const vector<CObj*> Get_Info(void) const { return m_vecInven; }

public:
	void Initialize();
	void Update();
	void Render_All_Item();
	void Render_Equiped_Item(); 


private:
	void Release();

public:
	bool Is_BuyItem(CObj* _pItem);
	bool Is_SellItem(int _iInput, int& _iMoney);

	void Equip_Item();
	void Unequip_Item();

private:
	CObj* m_pPlayer;
	// 인벤토리 
	vector<CObj*> m_vecInven;
	const size_t m_iSize;

};

