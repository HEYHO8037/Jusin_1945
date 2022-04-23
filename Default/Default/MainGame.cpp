#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Cloud.h"
#include "PlayerHp.h"
#include "MonsterHp.h"
#include "Life.h"
#include "Monster.h"
#include "Plane.h"
#include "SuicidePlane.h"

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

	//플레이어 생성시 hp바 생성
	float fXtemp = dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Get_Info().fX;
	float fYtemp = dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Get_Info().fY;
	if (!m_ObjList[OBJ_PLAYER].empty()) 
	{
		m_UiList[UI_PLAYERHP].push_back(CAbstractFactory<CPlayerHp>::UICreate(fXtemp, fYtemp-40));
	}

	//플레이어의 정보를 hp에 넣어주기

	m_UiList[UI_MONSTERHP].push_back(CAbstractFactory<CMonsterHp>::UICreate());
	
	for (int i = 0; i < 3; ++i)
	{
		m_UiList[UI_CLOUD].push_back(CAbstractFactory<CCloud>::UICreate(float((rand() % 50 +10)*(rand()% 12 +1)), float((-rand() % 30 + 1) * 15) - 10));
	}

	int iTemp = 0;
	for (int i = 0; i < 3; ++i)
	{
		m_UiList[UI_LIFE].push_back(CAbstractFactory<CLife>::UICreate( (50.f+iTemp) , 930.f));
		iTemp += 70;
	}
	
	m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create()); 
	/*TestItem = new CItem;
	TestItem->Initialize();*/
	CObj* player = m_ObjList[OBJ_PLAYER].front();

	CObj* boss = CAbstractFactory<CMonster>::Create();
	dynamic_cast<CMonster*>(boss)->BehaviorStart(player, &m_ObjList[OBJ_BULLET]);
	m_ObjList[OBJ_MONSTER].push_back(boss);

	CObj* plane = CAbstractFactory<CPlane>::Create();
	dynamic_cast<CMonster*>(plane)->BehaviorStart(player, &m_ObjList[OBJ_BULLET]);
	m_ObjList[OBJ_MONSTER].push_back(plane);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->SetObjList(&m_ObjList[OBJ_BULLET]);

	//자살공격하는 비행기
	//나중에 create 생성자 있는 버전으로 넣어주기
	CObj* suicide_plane = CAbstractFactory<CSuicidePlane>::Create();
	dynamic_cast<CMonster*>(suicide_plane)->BehaviorStart(player, nullptr);
	m_ObjList[OBJ_MONSTER].push_back(suicide_plane);

}

void CMainGame::Update(void)
{
	//플레이어의 실시간 좌표 hp클래스에 넘겨주기
	dynamic_cast<CPlayerHp*>(m_UiList[UI_PLAYERHP].front())->SetPlayerInfo(dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->GetPlayerInfo());


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
	HBITMAP backBitmap = NULL;
	HBITMAP backBitmapStage = NULL;
	HDC backHDC = CreateCompatibleDC(m_hDC);
	backBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	backBitmapStage = (HBITMAP)SelectObject(backHDC, backBitmap);
	//Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	Rectangle(backHDC, 0, 0, WINCX, WINCY);
	Rectangle(backHDC, 100, 100, WINCX - 100, WINCY - 100);

	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Monster : %d", m_ObjList[OBJ_MONSTER].size());
	TextOut(backHDC, 200, 200, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"??? : %d", m_ObjList[OBJ_BULLET].size());
	TextOut(backHDC, 200, 180, szBuff, lstrlen(szBuff));

	for (auto & iter : m_UiList[UI_CLOUD])
		iter->Render(backHDC);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto & iter : m_ObjList[i])
			iter->Render(backHDC);
	}


	TCHAR	szBuff1[32] = L"";
	swprintf_s(szBuff1, L"SCORE : %d", 1000);
	TextOut(backHDC, 600, 50, szBuff1, lstrlen(szBuff1));

	TCHAR	szBuff2[32] = L"";
	swprintf_s(szBuff2, L"KILL : %d", 30);
	TextOut(backHDC, 650, 950, szBuff2, lstrlen(szBuff2));

	TCHAR	szBuff3[32] = L"";
	//PLAYER level
	swprintf_s(szBuff3, L"LEVEL %d", 1);
	TextOut(backHDC, 350, 950, szBuff3, lstrlen(szBuff3));
	//TestItem->Render(m_hDC);
	

	for (int i = UI_LIFE; i < UI_END; ++i)
	{
		for (auto & iter : m_UiList[i])
			iter->Render(backHDC);
	}
	
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(backHDC, backBitmapStage));
	DeleteDC(backHDC);
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

