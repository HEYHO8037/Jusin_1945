#include "stdafx.h"
#include "Barrier.h"
#include "Bullet.h"
#include "Boss1.h"
#include "Plane.h"
#include "SuicidePlane.h"


CBarrier::CBarrier()
	: m_pPlayerInfo(nullptr),
	  m_fAngle(0.f),
	  m_iRotate(0)
{
}


CBarrier::~CBarrier()
{
}

void CBarrier::Initialize(void)
{
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 0.f;
	m_fAngle = 0.f;

	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 10.f;
}

int CBarrier::Update(void)
{
	UpdatePos();
	m_tInfo.fX += ((m_tInfo.fCX + m_pPlayerInfo->fCX) * sinf(RADIAN * m_fAngle));
	m_tInfo.fY += ((m_tInfo.fCY + m_pPlayerInfo->fCY) * cosf(RADIAN * m_fAngle));
	Update_Rect();

	return 0;
}

void CBarrier::Late_Update(void)
{
	m_fAngle += m_fSpeed;

	if ((int)m_fAngle % 360 == 0)
	{
		m_iRotate++;
	}

}

void CBarrier::Render(HDC hDC)
{
	HBRUSH brush;
	HPEN pen;

	pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	brush = CreateSolidBrush(RGB(200, 200, 200));
	SelectObject(hDC, pen);
	SelectObject(hDC, brush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	DeleteObject(pen);
	DeleteObject(brush);
}

void CBarrier::Release(void)
{
	m_pPlayerInfo = nullptr;
}

void CBarrier::CollisionEnter(CObj * _sour)
{

	if (dynamic_cast<CBullet*>(_sour)->GetType() == PLAYER_BULLET)
	{
		return;
	}


	if (dynamic_cast<CBullet*>(_sour)->GetType() == MONSTER_BULLET)
	{
		_sour->Set_Dead();
	}
	else if (dynamic_cast<CPlane*>(_sour)->GetHP() == 1)
	{
		_sour->Set_Dead();
	}
	else if (dynamic_cast<CSuicidePlane*>(_sour)->GetHP() == 1)
	{
		_sour->Set_Dead();
	}
	else if (dynamic_cast<CBoss1*>(_sour)->GetHP() != 0)
	{
		dynamic_cast<CMonster*>(_sour)->Hit();
	}
}

void CBarrier::SetPlayerInfo(INFO * pPlayerInfo)
{
	m_pPlayerInfo = pPlayerInfo;

	m_tInfo.fX = m_pPlayerInfo->fX;
	m_tInfo.fY = m_pPlayerInfo->fY;
}

int CBarrier::GetRotateRate() const
{
	return m_iRotate;
}

void CBarrier::UpdatePos()
{
	m_tInfo.fX = m_pPlayerInfo->fX;
	m_tInfo.fY = m_pPlayerInfo->fY;
}
