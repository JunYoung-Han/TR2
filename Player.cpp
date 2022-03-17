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
	cout << "�̸� : " << m_tInfo.szName << endl;
	cout << "���� : " << m_tInfo.iLevel << endl;
	cout << "���ݷ� : " << m_tInfo.iAttack << endl;
	cout << "ü�� / �ִ� ü�� : " << m_tInfo.iHp << " / " << m_tInfo.iMaxHp << endl;
	cout << "����ġ / �ִ� ����ġ : " << m_tInfo.iExp << " / " << m_tInfo.iMaxExp << endl;
	cout << "������ : " << m_tInfo.iMoney << endl;
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

	cout << "������ �����ϼ���. (1. ����  2, ������  3. ����  4. �ҷ�����  5. ����) : ";
	cin >> iInput;

	switch (iInput)
	{
	case 1:
		strcpy_s(m_tInfo.szName, 32, "����");
		m_tInfo.iAttack = 10;
		m_tInfo.iMaxHp = 100;
		m_tInfo.iHp = m_tInfo.iMaxHp;
		m_tInfo.iMaxExp = 100;
		m_tInfo.iExp = 0;
		m_tInfo.iLevel = 1;
		m_tInfo.iMoney = 100000;
		break;

	case 2:
		strcpy_s(m_tInfo.szName, 32, "������");
		m_tInfo.iAttack = 10;
		m_tInfo.iMaxHp = 100;
		m_tInfo.iHp = m_tInfo.iMaxHp;
		m_tInfo.iMaxExp = 100;
		m_tInfo.iExp = 0;
		m_tInfo.iLevel = 1;
		m_tInfo.iMoney = 100000;
		break;

	case 3:
		strcpy_s(m_tInfo.szName, 32, "����");
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
	// �Ű����� �������� ������ Ÿ�� �޾ƿ�.
	ITEMTYPE	eItemType = dynamic_cast<CItem*>(pItem)->Get_ItemType();

	// ������ �����Ǿ��ִ� �������� ���� ���, ���� �� ������ ������.
	// ������ ������ �ƴ� ���������̱� ������ �������� Delete �� �ʿ�� ����.
	if (nullptr != m_pItem[eItemType])
	{
		// ������ �ɷ�ġ ����
		Adjust_Item_Ability(-m_pItem[eItemType]->Get_Info().iAttack, -m_pItem[eItemType]->Get_Info().iHp);
		// �ش罽�� ����.
		dynamic_cast<CItem*>(m_pItem[eItemType])->Set_Equip(false);
		m_pItem[eItemType] = nullptr;
	}

	// ������ ����
	// ������ �ɷ�ġ ����
	Adjust_Item_Ability(pItem->Get_Info().iAttack, pItem->Get_Info().iHp);
	m_pItem[eItemType] = pItem;
	dynamic_cast<CItem*>(m_pItem[eItemType])->Set_Equip(true);
}

void CPlayer::Unequip_Item(CObj* pItem)
{
	ITEMTYPE	eItemType = dynamic_cast<CItem*>(pItem)->Get_ItemType();

	if (nullptr != m_pItem[eItemType])
	{
		// ������ �ɷ�ġ ����
		Adjust_Item_Ability(-m_pItem[eItemType]->Get_Info().iAttack, -m_pItem[eItemType]->Get_Info().iHp);
		// �ش罽�� ����.
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

		cout << "�ҷ����� ����" << endl;
		fclose(fp);
	}
	else
		cout << "�ҷ����� ����" << endl;
	system("pause");
}

void CPlayer::Adjust_Item_Ability(int _iAttack, int _iHp)
{
	m_tInfo.iAttack += _iAttack;
	m_tInfo.iMaxHp += _iHp;
}