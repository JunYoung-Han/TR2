#include "pch.h"
#include "Store.h"

CStore::CStore()
	: m_pPlayer(nullptr)
	, m_pInven(nullptr)
{
	// �����ۺ��� ���� ũ�� �̸� �Ҵ�
	m_vecItem[ITEM_WEAPON].reserve(3);
	m_vecItem[ITEM_ARMOR].reserve(3);
}

CStore::~CStore()
{
	Release();
}

void CStore::Initialize()
{
	// �����
	CItem* pItem = new CItem("�ʱް�", 10, 0, 1);
	pItem->Set_Money(1000);
	pItem->Set_ItemType(ITEM_WEAPON);
	m_vecItem[ITEM_WEAPON].push_back(pItem);

	pItem = new CItem("�߱ް�", 20, 0, 2);
	pItem->Set_Money(2000);
	pItem->Set_ItemType(ITEM_WEAPON);
	m_vecItem[ITEM_WEAPON].push_back(pItem);

	pItem = new CItem("��ް�", 30, 0, 3);
	pItem->Set_Money(3000);
	pItem->Set_ItemType(ITEM_WEAPON);
	m_vecItem[ITEM_WEAPON].push_back(pItem);

	// ��
	pItem = new CItem("�ʱ޿�", 0, 10, 1);
	pItem->Set_Money(1000);
	pItem->Set_ItemType(ITEM_ARMOR);
	m_vecItem[ITEM_ARMOR].push_back(pItem);

	pItem = new CItem("�߱޿�", 0, 20, 2);
	pItem->Set_Money(2000);
	pItem->Set_ItemType(ITEM_ARMOR);
	m_vecItem[ITEM_ARMOR].push_back(pItem);

	pItem = new CItem("��޿�", 0, 30, 3);
	pItem->Set_Money(3000);
	pItem->Set_ItemType(ITEM_ARMOR);
	m_vecItem[ITEM_ARMOR].push_back(pItem);

}

void CStore::Update()
{
	int iInput = 0;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();

		cout << "1. �������  2. �� ����  3. �Ǹ�  4. ���ܰ� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			Render(ITEM_WEAPON);
			break;

		case 2:
			Render(ITEM_ARMOR);
			break;

		case 3:
			Sell_Item();
			break;

		case 4:
			return;

		default:
			continue;
		}
	}
}

void CStore::Render(ITEMTYPE _eType)
{
	int iInput = 0;

	while (true)
	{
		system("cls");
		m_pPlayer->Render();

		int i = 1;
		for (const auto& iter : m_vecItem[_eType])
		{
			cout << i << ". �� : " << endl;
			iter->Render();
			++i;
		}

		cout << "������ ������ ��ȣ ���� (4�� : ���ܰ�)";
		cin >> iInput;
		if (4 == iInput)
			return;

		Buy_Item(m_vecItem[_eType][iInput - 1]);
	}
}

void CStore::Release()
{
	for (int i = 0; i < ITEM_END; ++i)
	{
		for_each(m_vecItem[i].begin(), m_vecItem[i].end(), CDeleteObj());
		m_vecItem[i].clear();
		vector<CObj*>().swap(m_vecItem[i]);
	}
	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CInven*>(m_pInven);
}

void CStore::Buy_Item(CObj* pItem)
{
	if (m_pPlayer->Get_Info().iMoney >= pItem->Get_Info().iMoney
		&& m_pInven->Is_BuyItem(pItem))
	{
		m_pPlayer->Buy_Item(pItem->Get_Info().iMoney);
		cout << "���ż���!" << endl;
	}
	else
	{
		cout << "�κ��丮 ĭ�� ���� á�ų� �Ǵ� �ܾ��� �����մϴ�." << endl;
	}
	system("pause");
}

void CStore::Sell_Item(void)
{
	int iInput = 0;

	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		m_pInven->Render_All_Item();

		cout << "0. ������ : ";
		cin >> iInput;

		--iInput;

		if (0 > iInput)
			return;
		if (5 <= iInput)
			continue;

		int iMoney = 0;

		if (m_pInven->Is_SellItem(iInput, iMoney))
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Plus_Money(iMoney);
			cout << "�Ǹż���!" << endl;
		}
		else
		{
			cout << "[�Ǹ� ����] �Ǹ��� �������� �����ϴ�." << endl;
		}
		system("pause");
	}
}
