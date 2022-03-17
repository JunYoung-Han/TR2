#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	CMonster(const char* _pName, int _iAttack, int _iMaxHp, int _iLevel = 1);
	virtual ~CMonster();

public:
	virtual void    Initialize()override;
	virtual void    Render()	override;
	virtual void    Release()	override;

};

