#include "pch.h"
#include "MainGame.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr)
	, m_pField(nullptr)
	, m_pStore(nullptr)
	, m_pInven(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}
	dynamic_cast<CPlayer*>(m_pPlayer)->SelectJob();
	if (nullptr == m_pInven)
	{
		m_pInven = new CInven;
		m_pInven->Set_Player(m_pPlayer);
		m_pInven->Initialize();
	}
}

void CMainGame::Update(void)
{
	int iInput = 0;

	while (true)
	{
		system("cls");
		m_pPlayer->Render();

		cout << "1. 사냥터  2. 상점  3. 인벤토리  4. 저장  5. 종료 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			if (nullptr == m_pField)
			{
				m_pField = new CField(m_pPlayer);
				m_pField->Initialize();
			}
			m_pField->Update();
			break;

		case 2:
			if (nullptr == m_pStore)
			{
				m_pStore = new CStore;
				m_pStore->Initialize();
				m_pStore->Set_Player(m_pPlayer);
				m_pStore->Set_Inven(m_pInven);
			}
			m_pStore->Update();
			break;

		case 3:
			if (nullptr != m_pInven)
				m_pInven->Update();
			break;

		case 4:
			Save_Data();
			break;

		case 5:
			return;

		default:
			break;
		}
	}
}

void CMainGame::Release(void)
{
	Safe_Delete<CInven*>(m_pInven);
	Safe_Delete<CStore*>(m_pStore);
	Safe_Delete<CField*>(m_pField);
	Safe_Delete<CObj*>(m_pPlayer);
}

void CMainGame::Save_Data(void)
{
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, "../Data/Save.dat", "wb");

	if (0 == err)
	{
		fwrite(&(m_pPlayer->Get_Info()), sizeof(INFO), 1, fp);
		// for()
		//fwrite(&(m_pInven->Get_Info()), sizeof(INFO), 1, fp);
		cout << "저장 성공" << endl;
		fclose(fp);
	}
	else
		cout << "저장 실패" << endl;

	system("pause");
}