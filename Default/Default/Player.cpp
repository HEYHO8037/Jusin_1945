#include "stdafx.h"
#include "Barrier.h"
#include "AssistantPlayer.h"
#include "Bullet.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "PlayerHp.h"

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
	m_tInfo.fY = 700.f;

	m_tInfo.fCX = (float)PlayerSize;
	m_tInfo.fCY = (float)PlayerSize;

	m_fSpeed = 10.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
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

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_pBarrier)
	{
		m_pBarrier->Late_Update();

		if (m_pBarrier->GetRotateRate() >= 10)
		{
			delete m_pBarrier;
			m_pBarrier = nullptr;
		}
	}


	CollisionWindow();
}

void CPlayer::Render(HDC hDC)
{
	HBRUSH brush;
	HPEN pen;

	pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	brush = CreateSolidBrush(RGB(0, 200, 200));
	SelectObject(hDC, pen);
	SelectObject(hDC, brush);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	DeleteObject(pen);
	DeleteObject(brush);

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
	m_bulletList = pObjList;
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

int* CPlayer::GetPowerUpItemCount()
{
	return &m_iPowerUpItemCount;
}

int* CPlayer::GetPlayerHP()
{
	return &m_iHP;
}

void CPlayer::PlayerHit()
{
	m_iHP -= 34;
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



	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		ShotGunFire();

		if (m_pAssistant[AST_LEFT])
		{
			for (int i = 0; i < AST_END; ++i)
			{
				m_pAssistant[i]->ShotGunFire();
			}
		}
	}

	if (GetAsyncKeyState('Z'))
	{
		InitBarrier();
	}
	if (GetAsyncKeyState('X'))
	{
		InitAssistantPlane();
	}
	
}

void CPlayer::NormalFire()
{
	int iDegree = -90;
	CObj* newBullet = CAbstractFactory<CBullet>::Create();
	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);
}

void CPlayer::ShotGunFire()
{
	int iDegree = -90;
	CObj* newBullet = CAbstractFactory<CBullet>::Create();
	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);

	iDegree -= 15;
	newBullet = CAbstractFactory<CBullet>::Create();
	BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);

	iDegree = -90;

	iDegree += 15;
	newBullet = CAbstractFactory<CBullet>::Create();
	BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);
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
	m_pAssistant[0]->SetPlayer(this);
	m_pAssistant[0]->SetObjList(m_bulletList);
	m_pAssistant[0]->SetSpeed(m_fSpeed);

	m_pAssistant[1] = new CAssistantPlayer(AST_RIGHT);
	m_pAssistant[1]->Initialize();
	m_pAssistant[1]->SetPlayer(this);
	m_pAssistant[1]->SetObjList(m_bulletList);
	m_pAssistant[1]->SetSpeed(m_fSpeed);
}
