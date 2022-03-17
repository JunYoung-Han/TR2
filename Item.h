#pragma once
#include "Obj.h"

class CItem :
	public CObj
{
public:
	CItem();
	CItem(const char* pName, int _iAttack, int _iMaxHp, int _iLevel = 1);
	CItem(CItem& rInfo);
	virtual ~CItem();

public:
	virtual void	Initialize() override;
	virtual void	Render()	 override;
	virtual void	Release()	 override;

public:
	void	Set_Money(int _iMoney) { m_tInfo.iMoney = _iMoney; }
	void	Set_ItemType(ITEMTYPE _eType) { m_eItemType = _eType; }
	void	Set_Equip(bool _bEquip) { m_bEquip = _bEquip; }
	bool	isEquiped(void) { return m_bEquip; }

	const ITEMTYPE& Get_ItemType(void) const { return m_eItemType; }


private:
	ITEMTYPE    m_eItemType = ITEM_END;
	bool        m_bEquip = false;
};