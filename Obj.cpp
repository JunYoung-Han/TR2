#include "pch.h"
#include "Obj.h"

CObj::CObj()
{
}

CObj::CObj(const char* _pName, int _iAttack, int _iMaxHp, int _iLevel)
	: m_tInfo(_pName, _iAttack, _iMaxHp, _iLevel)
{
}

CObj::CObj(CObj& rObj)
	: m_tInfo(rObj.m_tInfo)
{
}

CObj::~CObj()
{
}