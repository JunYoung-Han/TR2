#pragma once

class CObj
{
public:
	CObj();
	CObj(const char* _pName, int _iAttack, int _iMaxHp, int _iLevel = 1);
	CObj(CObj& rObj);
	virtual ~CObj();

public:
	const INFO& Get_Info(void) const { return m_tInfo; }
	void		Set_Damage(int _iAttack) { m_tInfo.iHp -= _iAttack; }
	void		Buy_Item(int _iPrice) { m_tInfo.iMoney -= _iPrice; }

public:
	virtual void	Initialize()	PURE;
	virtual void	Render()		PURE;
	virtual void	Release()		PURE;

protected:
	INFO	m_tInfo;
};

