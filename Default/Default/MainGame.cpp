#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"

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
	m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create()); // 임시 테스트(OBJ_list의 배열 요소 값인 enum을 추가해도 되는지 몰라서 플레이어로 테스트)
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
	//TestItem->Update();
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
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto & iter : m_ObjList[i])
			iter->Render(m_hDC);
	}
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

	ReleaseDC(g_hWnd, m_hDC);
}

