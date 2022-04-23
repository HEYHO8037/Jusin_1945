#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Cloud.h"
#include "PlayerHp.h"
#include "MonsterHp.h"
#include "Life.h"
CMainGame::CMainGame()
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	srand(unsigned(time(nullptr))); //��� �־������

	m_hDC = GetDC(g_hWnd);
	
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());

	if (!m_ObjList[OBJ_PLAYER].empty()) // �÷��̾� ��ǥ ���ͼ� ��ü �����ϱ�
	{
		m_UiList[UI_PLAYERHP].push_back(CAbstractFactory<CPlayerHp>::UICreate());
	}

	//boss���Ͱ� ������ monsterHp ����, monster�� ����
	m_UiList[UI_MONSTERHP].push_back(CAbstractFactory<CMonsterHp>::UICreate());
	
	//cloud �Ϸ�
	for (int i = 0; i < 3; ++i)
	{
		m_UiList[UI_CLOUD].push_back(CAbstractFactory<CCloud>::UICreate(float((rand() % 50 +10)*(rand()% 12 +1)), float((-rand() % 30 + 1) * 15) - 10));
	}

	//life ����, �÷��̾��� hp�� ����
	int iTemp = 0;
	for (int i = 0; i < 3; ++i)
	{
		m_UiList[UI_LIFE].push_back(CAbstractFactory<CLife>::UICreate( (50.f+iTemp) , 930.f));
		iTemp += 70;
	}
	
	m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create()); // �ӽ� �׽�Ʈ(OBJ_list�� �迭 ��� ���� enum�� �߰��ص� �Ǵ��� ���� �÷��̾�� �׽�Ʈ)
	/*TestItem = new CItem;
	TestItem->Initialize();*/
}

void CMainGame::Update(void)
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_UiList[i].begin();
			iter != m_UiList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CUi*>(*iter);
				iter = m_UiList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	//TestItem->Update();
}

void CMainGame::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto & iter : m_ObjList[i])
			iter->Late_Update();
	}

	for (int i = 0; i < UI_END; ++i)
	{
		for (auto & iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	for (int i = 0; i < UI_END; ++i)
	{
		for (auto & iter : m_UiList[i])
			iter->Render(m_hDC);
	}

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto & iter : m_ObjList[i])
			iter->Render(m_hDC);
	}


	//��Ʈ���
	TCHAR	szBuff[32] = L"";
	//1000�ڸ��� get_scroe
	swprintf_s(szBuff, L"SCORE : %d", 1000);
	TextOut(m_hDC, 600, 50, szBuff, lstrlen(szBuff));

	TCHAR	szBuff2[32] = L"";
	//30�ڸ��� ���� ���� ���� �ֱ�
	swprintf_s(szBuff2, L"KILL : %d", 30);
	TextOut(m_hDC, 650, 950, szBuff2, lstrlen(szBuff2));

	TCHAR	szBuff3[32] = L"";
	//PLAYER level
	swprintf_s(szBuff3, L"LEVEL %d", 1);
	TextOut(m_hDC, 350, 950, szBuff3, lstrlen(szBuff3));
	//TestItem->Render(m_hDC);
}

void CMainGame::Release(void)
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}

	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UiList[i])
			Safe_Delete<CUi*>(iter);

		m_ObjList[i].clear();
	}


	ReleaseDC(g_hWnd, m_hDC);
}

