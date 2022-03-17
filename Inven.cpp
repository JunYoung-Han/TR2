#include "pch.h"
#include "Inven.h"

CInven::CInven()
	: m_pPlayer(nullptr)
	, m_iSize(5)
{
}

CInven::~CInven()
{
	Release();
}

void CInven::Initialize()
{
	// ���� ���� �̸� Ȯ��
	m_vecInven.reserve(m_iSize);
}

void CInven::Update()
{
	int iInput = 0;

	while (true)
	{
		system("cls");
		m_pPlayer->Render();

		cout << "1. ����  2. ����  3. �� �ܰ� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			Equip_Item();
			break;

		case 2:
			Unequip_Item();
			break;

		case 3:
			return;

		default:
			continue;
		}
	}

}

void CInven::Render_All_Item()
{
	for (size_t i = 0; i < m_vecInven.size(); ++i)
	{
		cout << i + 1 << ". ";
		// Item ��ü�� �Ҵ���� CObj ������ �̱� ������ Item�� Render_All_Item �Լ��� ȣ���Ѵ�.
		m_vecInven[i]->Render();
	}
}

void CInven::Render_Equiped_Item()
{
	for (size_t i = 0; i < m_vecInven.size(); ++i)
	{
		if (dynamic_cast<CItem*>(m_vecInven[i])->isEquiped())
		{
			cout << i + 1 << ". ";
			m_vecInven[i]->Render();
		}
	}
}

void CInven::Release()
{
	for_each(m_vecInven.begin(), m_vecInven.end(), CDeleteObj());
	m_vecInven.clear();
	vector<CObj*>().swap(m_vecInven);
}

bool CInven::Is_BuyItem(CObj* _pItem)
{
	// �κ��丮 ĭ���� �������� ������ ���� ���
	if (m_iSize <= m_vecInven.size())
		return false;

	// �̷��� �ϸ� CStore�� �ִ� item�� �ּҸ� �״�� �������� ������ �ȵȴ�. (���� ����)
	// m_vecInven.push_back(_pItem);

	// CItem ��ü�� �����Ҵ��� �޾ұ� ������ ������ ���� ���� ���縦 ���־�� �Ѵ�.
	// Item��ü�� �����Ҵ� ���� CObj �����͸� ���� �����ϱ�.
	// ù��° ���
	// CItem* pCopyItem = dynamic_cast<CItem*>(_pItem);
	// CObj* pOcj = new CItem(*pCopyItem);
	// �ι�° ���
	CObj* pObj = new CItem(*dynamic_cast<CItem*>(_pItem));

	// �ش� �������� �κ��� �ְ� true ��ȯ
	m_vecInven.push_back(pObj);
	return true;
}

bool CInven::Is_SellItem(int _iInput, int& _iMoney)
{
	auto iter = m_vecInven.begin();
	iter += _iInput;

	_iMoney = (*iter)->Get_Info().iMoney >> 1; // �ݰ����� �Ǹ�.

	Safe_Delete<CObj*>(*iter);
	m_vecInven.erase(iter);

	return true;
}

void CInven::Equip_Item()
{
	int iInput = 0;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render_All_Item();

		cout << "0. ������ : ";
		cin >> iInput;
		--iInput;

		if (0 > iInput)
			return;

		if ((size_t)iInput >= m_vecInven.size())
			continue;

		dynamic_cast<CPlayer*>(m_pPlayer)->Equip_Item(m_vecInven[iInput]);
	}
}

void CInven::Unequip_Item()
{
	int iInput = 0;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render_Equiped_Item();

		cout << "0. ������ : ";
		cin >> iInput;
		--iInput;

		if (0 > iInput)
			return;

		if ((size_t)iInput >= m_vecInven.size())
			continue;

		dynamic_cast<CPlayer*>(m_pPlayer)->Unequip_Item(m_vecInven[iInput]);
	}
}
