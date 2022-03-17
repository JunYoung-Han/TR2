#pragma once
#include "Obj.h"
#include "Item.h"

class CPlayer :
    public CObj
{
public:
    CPlayer();
    CPlayer(const char* _pName, int _iAttack, int _iMaxHp, int _iLevel);
    virtual ~CPlayer();

public:
    virtual void Initialize()   override;
    virtual void Render()       override;
    virtual void Release()      override;

public:
    void    SelectJob(void);
    void    Set_Hp(int _iMaxHp) { m_tInfo.iHp = _iMaxHp; }
    void    Plus_Money(int _iMoney) { m_tInfo.iMoney += _iMoney; }

public:
    void    Combat_Win(int _iExp, int _iMoney);
    void    Combat_Lose();
    void    Combat_Run();
    void    Equip_Item(CObj* pItem);
    void    Unequip_Item(CObj* pItem);

private:
    void    Load_Data(void);
    void    Adjust_Item_Ability(int _iAttack, int _iHp);

private:
    CObj* m_pItem[ITEM_END];
};