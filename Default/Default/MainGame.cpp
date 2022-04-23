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
	srand(unsigned(time(nullptr)));
	
	m_hDC = GetDC(g_hWnd);

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());

	//플레이어, 몬스터 hp
	m_ObjList[OBJ_PLAYERHP].push_back(CAbstractFactory<CPlayerHp>::Create());
	m_ObjList[OBJ_MONSTERHP].push_back(CAbstractFactory<CMonsterHp>::Create());
	
	//구름 생성완료 충돌처리
	for (int i = 0; i < (rand() % 3 + 1); ++i)
	{
		m_UiList[UI_CLOUD].push_back(CAbstractFactory<CCloud>::CreateUi(float((rand() % 50 +10)*(rand()% 12 +1)), float((-rand() % 30 + 1) * 15) - 10));
	}

	//life 생성
	int iTemp = 0;
	for (int i = 0; i < 3; ++i)
	{
		m_UiList[UI_LIFE].push_back(CAbstractFactory<CLife>::CreateUi( (70.f+iTemp) , 900.f));
		iTemp += 70;
	}
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


	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"SCORE : %d", 1000);
	TextOut(m_hDC, 600, 50, szBuff, lstrlen(szBuff));
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

