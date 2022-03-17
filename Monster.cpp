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
	cout << "�̸� : " << m_tInfo.szName << endl;
	cout << "���ݷ� : " << m_tInfo.iAttack << endl;
	cout << "ü�� : " << m_tInfo.iHp << endl;
	cout << "����ġ : " << m_tInfo.iExp << endl;
	cout << "������ : " << m_tInfo.iMoney << endl;
}

void CMonster::Release()
{
}
