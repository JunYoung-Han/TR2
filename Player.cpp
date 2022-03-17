#include "pch.h"
#include "Player.h"

CPlayer::CPlayer()
	: CObj()
{
	memset(m_pItem, 0, sizeof(m_pItem));
}

CPlayer::CPlayer(const char* _pName, int _iAttack, int _iMaxHp, int _iLevel)
	: CObj(_pName, _iAttack, _iMaxHp, _iLevel)
{
	memset(m_pItem, 0, sizeof(m_pItem));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{

}

void CPlayer::Render()
{
	cout << "====================================" << endl;
	cout << "이름 : " << m_tInfo.szName << endl;
	cout << "레벨 : " << m_tInfo.iLevel << endl;
	cout << "공격력 : " << m_tInfo.iAttack << endl;
	cout << "체력 / 최대 체력 : " << m_tInfo.iHp << " / " << m_tInfo.iMaxHp << endl;
	cout << "경험치 / 최대 경험치 : " << m_tInfo.iExp << " / " << m_tInfo.iMaxExp << endl;
	cout << "소지금 : " << m_tInfo.iMoney << endl;
	cout << "====================================" << endl;
}

void CPlayer::Release()
{
	for (auto& iter : m_pItem)
	{
		Safe_Delete<CObj*>(iter);
	}
}

void CPlayer::SelectJob(void)
{
	int iInput = 0;

	cout << "직업을 선택하세요. (1. 전사  2, 마법사  3. 도적  4. 불러오기  5. 종료) : ";
	cin >> iInput;

	switch (iInput)
	{
	case 1:
		strcpy_s(m_tInfo.szName, 32, "전사");
		m_tInfo.iAttack = 10;
		m_tInfo.iMaxHp = 100;
		m_tInfo.iHp = m_tInfo.iMaxHp;
		m_tInfo.iMaxExp = 100;
		m_tInfo.iExp = 0;
		m_tInfo.iLevel = 1;
		m_tInfo.iMoney = 100000;
		break;

	case 2:
		strcpy_s(m_tInfo.szName, 32, "마법사");
		m_tInfo.iAttack = 10;
		m_tInfo.iMaxHp = 100;
		m_tInfo.iHp = m_tInfo.iMaxHp;
		m_tInfo.iMaxExp = 100;
		m_tInfo.iExp = 0;
		m_tInfo.iLevel = 1;
		m_tInfo.iMoney = 100000;
		break;

	case 3:
		strcpy_s(m_tInfo.szName, 32, "도적");
		m_tInfo.iAttack = 10;
		m_tInfo.iMaxHp = 100;
		m_tInfo.iHp = m_tInfo.iMaxHp;
		m_tInfo.iMaxExp = 100;
		m_tInfo.iExp = 0;
		m_tInfo.iLevel = 1;
		m_tInfo.iMoney = 100000;
		break;

	case 4:
		Load_Data();
		break;

	case 5:
		return;

	default:
		break;
	}
}

void CPlayer::Combat_Win(int _iExp, int _iMoney)
{
	m_tInfo.iExp += _iExp;
	m_tInfo.iMoney += _iMoney;

	if (m_tInfo.iExp >= m_tInfo.iMaxExp)
	{
		++m_tInfo.iLevel;
		m_tInfo.iExp -= m_tInfo.iMaxExp;
		m_tInfo.iMaxExp *= 1.1;
		m_tInfo.iMaxHp *= 1.1;
		m_tInfo.iAttack *= 1.1;
		m_tInfo.iHp = m_tInfo.iMaxHp;
	}
}

void CPlayer::Combat_Lose()
{
	m_tInfo.iExp = 0;
}

void CPlayer::Combat_Run()
{
	m_tInfo.iMoney >> 1;
}

void CPlayer::Equip_Item(CObj* pItem)
{
	// 매개변수 아이템의 아이템 타입 받아옴.
	ITEMTYPE	eItemType = dynamic_cast<CItem*>(pItem)->Get_ItemType();

	// 기존에 장착되어있는 아이템이 있을 경우, 먼저 그 아이템 해제함.
	// 아이템 삭제가 아닌 장착해제이기 때문에 아이템을 Delete 할 필요는 없음.
	if (nullptr != m_pItem[eItemType])
	{
		// 아이템 능력치 해제
		Adjust_Item_Ability(-m_pItem[eItemType]->Get_Info().iAttack, -m_pItem[eItemType]->Get_Info().iHp);
		// 해당슬롯 비우기.
		dynamic_cast<CItem*>(m_pItem[eItemType])->Set_Equip(false);
		m_pItem[eItemType] = nullptr;
	}

	// 아이템 장착
	// 아이템 능력치 적용
	Adjust_Item_Ability(pItem->Get_Info().iAttack, pItem->Get_Info().iHp);
	m_pItem[eItemType] = pItem;
	dynamic_cast<CItem*>(m_pItem[eItemType])->Set_Equip(true);
}

void CPlayer::Unequip_Item(CObj* pItem)
{
	ITEMTYPE	eItemType = dynamic_cast<CItem*>(pItem)->Get_ItemType();

	if (nullptr != m_pItem[eItemType])
	{
		// 아이템 능력치 해제
		Adjust_Item_Ability(-m_pItem[eItemType]->Get_Info().iAttack, -m_pItem[eItemType]->Get_Info().iHp);
		// 해당슬롯 비우기.
		dynamic_cast<CItem*>(m_pItem[eItemType])->Set_Equip(false);
		m_pItem[eItemType] = nullptr;
	}
}

void CPlayer::Load_Data(void)
{
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, "../Data/Save.dat", "rb");

	if (0 == err)
	{
		INFO tInfo = {};

		fread(&tInfo, sizeof(INFO), 1, fp);

		m_tInfo = tInfo;

		cout << "불러오기 성공" << endl;
		fclose(fp);
	}
	else
		cout << "불러오기 실패" << endl;
	system("pause");
}

void CPlayer::Adjust_Item_Ability(int _iAttack, int _iHp)
{
	m_tInfo.iAttack += _iAttack;
	m_tInfo.iMaxHp += _iHp;
}