#include "pch.h"
#include "Monster.h"

CMonster::CMonster()
	: CObj()
{
}

CMonster::CMonster(const char* _pName, int _iAttack, int _iMaxHp, int _iLevel)
	: CObj(_pName, _iAttack, _iMaxHp, _iLevel)
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.iExp = rand() % 50 + ((m_tInfo.iLevel - 1) * 50);
	m_tInfo.iMoney = rand() % 5000 + ((m_tInfo.iLevel - 1) * 50);
	m_tInfo.iMaxExp = m_tInfo.iExp;
}

void CMonster::Render()
{
	cout << "==============================" << endl;
	cout << "이름 : " << m_tInfo.szName << endl;
	cout << "공격력 : " << m_tInfo.iAttack << endl;
	cout << "체력 : " << m_tInfo.iHp << endl;
	cout << "경험치 : " << m_tInfo.iExp << endl;
	cout << "소지금 : " << m_tInfo.iMoney << endl;
}

void CMonster::Release()
{
}
