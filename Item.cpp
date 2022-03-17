#include "pch.h"
#include "Item.h"

CItem::CItem()
	: CObj()
{
}

CItem::CItem(const char* pName, int _iAttack, int _iMaxHp, int _iLevel)
	: CObj(pName, _iAttack, _iMaxHp, _iLevel)
{
}

CItem::CItem(CItem& rInfo)
	: CObj(rInfo)
	, m_eItemType(rInfo.m_eItemType)
	, m_bEquip(rInfo.m_bEquip)
{
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
}

void CItem::Render()
{
	cout << "�̸� : " << m_tInfo.szName << endl;
	cout << "���ݷ� : " << m_tInfo.iAttack << endl;
	cout << "ü�� : " << m_tInfo.iHp << endl;
	cout << "���� : " << m_tInfo.iMoney << endl;
	cout << "==============================" << endl;
}

void CItem::Release()
{
}
