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
	// 벡터 공간 미리 확보
	m_vecInven.reserve(m_iSize);
}

void CInven::Update()
{
	int iInput = 0;

	while (true)
	{
		system("cls");
		m_pPlayer->Render();

		cout << "1. 장착  2. 해제  3. 전 단계 : ";
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
		// Item 객체를 할당받은 CObj 포인터 이기 때문에 Item의 Render_All_Item 함수를 호출한다.
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
	// 인벤토리 칸보다 아이템의 개수가 많은 경우
	if (m_iSize <= m_vecInven.size())
		return false;

	// 이렇게 하면 CStore에 있는 item의 주소를 그대로 가져오기 때문에 안된다. (얕은 복사)
	// m_vecInven.push_back(_pItem);

	// CItem 객체로 동적할당을 받았기 때문에 다음과 같이 깊은 복사를 해주어야 한다.
	// Item객체로 동적할당 받은 CObj 포인터를 깊은 복사하기.
	// 첫번째 방법
	// CItem* pCopyItem = dynamic_cast<CItem*>(_pItem);
	// CObj* pOcj = new CItem(*pCopyItem);
	// 두번째 방법
	CObj* pObj = new CItem(*dynamic_cast<CItem*>(_pItem));

	// 해당 아이템을 인벤에 넣고 true 반환
	m_vecInven.push_back(pObj);
	return true;
}

bool CInven::Is_SellItem(int _iInput, int& _iMoney)
{
	auto iter = m_vecInven.begin();
	iter += _iInput;

	_iMoney = (*iter)->Get_Info().iMoney >> 1; // 반값으로 판매.

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

		cout << "0. 나가기 : ";
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

		cout << "0. 나가기 : ";
		cin >> iInput;
		--iInput;

		if (0 > iInput)
			return;

		if ((size_t)iInput >= m_vecInven.size())
			continue;

		dynamic_cast<CPlayer*>(m_pPlayer)->Unequip_Item(m_vecInven[iInput]);
	}
}
