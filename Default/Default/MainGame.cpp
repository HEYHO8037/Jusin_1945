#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"

#include "Monster.h"
#include "Plane.h"

CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());

	CObj* player = m_ObjList[OBJ_PLAYER].front();

	CObj* boss = CAbstractFactory<CMonster>::Create();
	dynamic_cast<CMonster*>(boss)->BehaviorStart(player, &m_ObjList[OBJ_BULLET]);
	m_ObjList[OBJ_MONSTER].push_back(boss);

	CObj* plane = CAbstractFactory<CPlane>::Create();
	dynamic_cast<CMonster*>(plane)->BehaviorStart(player, &m_ObjList[OBJ_BULLET]);
	m_ObjList[OBJ_MONSTER].push_back(plane);
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
}

void CMainGame::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto & iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CMainGame::Render(void)
{
	HDC backHDC = CreateCompatibleDC(m_hDC);
	HBITMAP backBitmap = NULL;
	HBITMAP backBitmapStage = NULL;

	backBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	backBitmapStage = (HBITMAP)SelectObject(backHDC, backBitmap);


	Rectangle(backHDC, 0, 0, WINCX, WINCY);
	Rectangle(backHDC, 100, 100, WINCX - 100, WINCY - 100);

	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Monster : %d", m_ObjList[OBJ_MONSTER].size());
	TextOut(backHDC, 200, 200, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"ÃÑ¾Ë : %d", m_ObjList[OBJ_BULLET].size());
	TextOut(backHDC, 200, 180, szBuff, lstrlen(szBuff));


	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto & iter : m_ObjList[i])
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

	ReleaseDC(g_hWnd, m_hDC);
}

