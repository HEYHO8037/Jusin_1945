#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Cloud.h"
#include "PlayerHp.h"
#include "MonsterHp.h"
#include "Life.h"
#include "Boss1.h"
#include "Plane.h"
#include "SuicidePlane.h"
#include "Bomb.h"
#include "CollisionMgr.h"

int CMainGame::killCount = 0;
bool CMainGame::bBoss = false;

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

	m_player = m_ObjList[OBJ_PLAYER].front();



	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->SetObjList(&m_ObjList[OBJ_BULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->SetMonsterList(&m_ObjList[OBJ_MONSTER]);

	//플레이어 생성시 hp바 생성
	float fXtemp = dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Get_Info().fX;
	float fYtemp = dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Get_Info().fY;
	if (!m_ObjList[OBJ_PLAYER].empty())
	{
		m_UiList[UI_PLAYERHP].push_back(CAbstractFactory<CPlayerHp>::UICreate(fXtemp, fYtemp - 40));
	}
	//playerHp에 player obj 넣기(front 사용 문제)
	dynamic_cast<CPlayerHp*>(m_UiList[UI_PLAYERHP].front())->SetObjInfo(m_player);

	//life 생성
	m_UiList[UI_LIFE].push_back(CAbstractFactory<CLife>::UICreate((50.f), 930.f));
	dynamic_cast<CLife*>(m_UiList[UI_LIFE].front())->SetObjInfo(m_player);
	//폭탄 생성
	m_UiList[UI_BOMB].push_back(CAbstractFactory<CBomb>::UICreate());
	dynamic_cast<CBomb*>(m_UiList[UI_BOMB].front())->SetObjInfo(m_player);
	//구름 생성
	for (int i = 0; i < 4; ++i)
	{
		m_UiList[UI_CLOUD].push_back(CAbstractFactory<CCloud>::UICreate(float((rand() % 50 + 30)*(rand() % 12 + 1)) + 10.f, float((-rand() % 60 + 1) * 15) - 20));
	}

	killCount = 0;

	m_timer = new CTimer;
	m_timer->StartTimer(ENERMY_PER_SECOND, [&]() {
		CObj* monsterObj = nullptr;
		switch(rand() % MonsterEnd) {
		case Plane: {
			float posX = rand() % WINCX + 100;
			float posY = rand() % (WINCY / 2) + 100;
			
			float startPosX = posX > (WINCX/2) ? WINCX + 100 : -100;

			monsterObj = CAbstractFactory<CPlane>::Create(startPosX, posY);
			CPlane* plane = dynamic_cast<CPlane*>(monsterObj);
			plane->BehaviorStart(m_player, &m_ObjList[OBJ_BULLET], &m_ObjList[OBJ_ITEM]);
			plane->SetAppearPosition(posX, posY);
		}
			break;

		case Suicide: {
			//돌진형 비행기
			/////////////////////
			monsterObj = CAbstractFactory<CPlane>::Create();
			CPlane* plane = dynamic_cast<CPlane*>(monsterObj);
			plane->BehaviorStart(m_player, &m_ObjList[OBJ_BULLET], &m_ObjList[OBJ_ITEM]);

			float posX = rand() % WINCX + 100;
			float posY = rand() % (WINCY / 2) + 100;
			plane->SetAppearPosition(posX, posY);
			/////////////////////

			//CObj* suicide_plane = CAbstractFactory<CSuicidePlane>::Create();
			//dynamic_cast<CMonster*>(suicide_plane)->BehaviorStart(player, &m_ObjList[OBJ_BULLET], nullptr);
			//m_ObjList[OBJ_MONSTER].push_back(suicide_plane);
		}
			break;
		}
		m_ObjList[OBJ_MONSTER].push_back(monsterObj);

		if (!bBoss && killCount > BOSS_APPEAR_COUNT) {
			CObj* bossObj = CAbstractFactory<CBoss1>::Create();
			CBoss1* boss = dynamic_cast<CBoss1*>(bossObj);
			boss->BehaviorStart(m_player, &m_ObjList[OBJ_BULLET], &m_ObjList[OBJ_ITEM]);
			boss->SetAppearPosition(WINCX / 2, 500);
			m_ObjList[OBJ_MONSTER].push_back(bossObj);

			CUi* newUI = CAbstractFactory<CMonsterHp>::UICreate();
			m_UiList[UI_MONSTERHP].push_back(newUI);
			dynamic_cast<CMonsterHp*>(newUI)->SetObjInfo(bossObj);

			bBoss = true;
		}
	});
}

void CMainGame::Update(void)
{
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_ObjListRect(dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->GetBarrierClass(), m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_ObjListRect(dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->GetBarrierClass(), m_ObjList[OBJ_BULLET]);

	//플레이어의 실시간 좌표 hp클래스에 넘겨주기
	if(!m_ObjList[OBJ_PLAYER].empty())
		dynamic_cast<CPlayerHp*>(m_UiList[UI_PLAYERHP].front())->SetPlayerInfo(dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->GetPlayerInfo());

	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_UiList[i].begin();
			iter != m_UiList[i].end(); )
		{
			if ((*iter)->GetObjInfo() && (*iter)->GetObjInfo()->GetDead()) {
				(*iter)->SetDead();
			}

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

	m_timer->Update();
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
		for (auto & iter : m_UiList[i])
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

	HBRUSH	brush;
	HGDIOBJ h_old_brush;
	brush = CreateSolidBrush(RGB(0, 106, 0));
	h_old_brush = SelectObject(backHDC, brush);
	Rectangle(backHDC, 0, 0, WINCY, WINCY);
	SelectObject(backHDC, h_old_brush);
	DeleteObject(brush);
	
	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Monster : %d", m_ObjList[OBJ_MONSTER].size());
	TextOut(backHDC, 200, 200, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"총알 : %d", m_ObjList[OBJ_BULLET].size());
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

