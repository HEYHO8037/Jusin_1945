#include "stdafx.h"
#include "Barrier.h"
#include "AssistantPlayer.h"
#include "Bullet.h"
#include "Player.h"

CPlayer::CPlayer()
	: m_pBarrier(nullptr),
	  m_iHP(100),
	  m_iPowerUpItemCount(0),
	  m_bIsBarrier(false)
{
	for (int i = 0; i < AST_END; ++i)
	{
		m_pAssistant[i] = nullptr;
	}
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 10.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	// 연산을 진행
	Key_Input();

	if (m_pBarrier)
	{
		m_pBarrier->Update();
	}

	if (m_pAssistant[AST_LEFT])
	{
		for (int i = 0; i < AST_END; ++i)
		{
			m_pAssistant[i]->Update();
		}
	}

	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_pBarrier)
	{
		m_pBarrier->Late_Update();
	}

	CollisionWindow();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	if (m_pBarrier)
	{
		m_pBarrier->Render(hDC);
	}

	if (m_pAssistant[AST_LEFT])
	{
		for (int i = 0; i < AST_END; ++i)
		{
			m_pAssistant[i]->Render(hDC);
		}
	}
}

void CPlayer::Release(void)
{
	if (m_pAssistant[AST_LEFT])
	{
		for (int i = 0; i < AST_END; ++i)
		{
			delete m_pAssistant[i];
			m_pAssistant[i] = nullptr;
		}
	}

	if (m_pBarrier)
	{
		delete m_pBarrier;
		m_pBarrier = nullptr;
	}
}

void CPlayer::SetObjList(list<CObj*>* pObjList)
{
	m_pObjList = pObjList;
}

void CPlayer::SetGetBarrierItem()
{
	m_bIsBarrier = true;
}

void CPlayer::SetGetPowerItem()
{
	m_iPowerUpItemCount++;
}

CBarrier * CPlayer::GetBarrierClass()
{
	return m_pBarrier;
}


void CPlayer::Key_Input(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if(GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else

		m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;

	}
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;


	//총알 만드는 코드

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_pObjList->push_back(new CBullet(m_tInfo, false));
	}

	//베리어 생성(임시키 지정)
	if (GetAsyncKeyState('Z'))
	{
		InitBarrier();
	}
	if (GetAsyncKeyState('X'))
	{
		InitAssistantPlane();
	}
	
}

void CPlayer::CollisionWindow()
{
	if (m_tRect.left < 0)
	{
		m_tInfo.fX = m_tInfo.fCX / 2.f;
		Update_Rect();
	}
	else if (m_tRect.right > WINCX)
	{
		m_tInfo.fX = WINCX - m_tInfo.fCX / 2.f;
		Update_Rect();
	}

	if (m_tRect.top < 0)
	{
		m_tInfo.fY = m_tInfo.fCY / 2.f;
		Update_Rect();
	}
	else if (m_tRect.bottom > WINCY)
	{
		m_tInfo.fY = WINCY - m_tInfo.fCY / 2.f;
		Update_Rect();
	}
}

void CPlayer::InitBarrier()
{
	if (!m_pBarrier)
	{
		m_pBarrier = new CBarrier();
		m_pBarrier->Initialize();
		m_pBarrier->SetPlayerInfo(&m_tInfo);
	}
}

void CPlayer::InitAssistantPlane()
{
	m_pAssistant[0] = new CAssistantPlayer(AST_LEFT);
	m_pAssistant[0]->Initialize();
	m_pAssistant[0]->SetPlayerInfo(&m_tInfo);
	m_pAssistant[0]->SetSpeed(m_fSpeed);

	m_pAssistant[1] = new CAssistantPlayer(AST_RIGHT);
	m_pAssistant[1]->Initialize();
	m_pAssistant[1]->SetPlayerInfo(&m_tInfo);
	m_pAssistant[1]->SetSpeed(m_fSpeed);
}
