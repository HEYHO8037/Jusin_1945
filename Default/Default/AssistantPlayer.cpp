#include "stdafx.h"
#include "AssistantPlayer.h"
#include "Bullet.h"
#include "Player.h"
#include "AbstractFactory.h"


CAssistantPlayer::CAssistantPlayer()
{
}

CAssistantPlayer::CAssistantPlayer(ASSISTANT_DIR eDir)
{
	m_eDir = eDir;
}


CAssistantPlayer::~CAssistantPlayer()
{
}

void CAssistantPlayer::Initialize(void)
{
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 10.f;
}

int CAssistantPlayer::Update(void)
{
	if (m_eDir == AST_LEFT)
	{
		m_tInfo.fX = m_pPlayer->Get_Info().fX - (m_pPlayer->Get_Info().fCX + m_tInfo.fCX + 2.f);
	}
	else
	{
		m_tInfo.fX = m_pPlayer->Get_Info().fX + (m_pPlayer->Get_Info().fCY + m_tInfo.fCX + 2.f);
	}

	m_tInfo.fY = m_pPlayer->Get_Info().fY;

	Update_Rect();
	return 0;
}

void CAssistantPlayer::Late_Update(void)
{
}

void CAssistantPlayer::Render(HDC hDC)
{
	HBRUSH brush;
	HPEN pen;

	pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	brush = CreateSolidBrush(RGB(200, 0, 200));
	SelectObject(hDC, pen);
	SelectObject(hDC, brush);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	DeleteObject(pen);
	DeleteObject(brush);
}

void CAssistantPlayer::Release(void)
{
	m_pPlayer = nullptr;
}

void CAssistantPlayer::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;

	if (m_eDir == AST_LEFT)
	{
		m_tInfo.fX = m_pPlayer->Get_Info().fX - m_tInfo.fCX + 2.f;
	}
	else
	{
		m_tInfo.fX = m_pPlayer->Get_Info().fX + m_tInfo.fCX + 2.f;
	}

	m_tInfo.fY = m_pPlayer->Get_Info().fY;
}

void CAssistantPlayer::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

void CAssistantPlayer::SetObjList(list<CObj*>* pObjList)
{
	m_bulletList = pObjList;
}

void CAssistantPlayer::NormalFire()
{
	int iDegree = -90;
	CObj* newBullet = CAbstractFactory<CBullet>::Create();
	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(iDegree * PI / 180.f), sinf(iDegree * PI / 180.f));
	BulletObj->SetType(PLAYER_BULLET);
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_bulletList->push_back(newBullet);
}

void CAssistantPlayer::ShotGunFire()
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
