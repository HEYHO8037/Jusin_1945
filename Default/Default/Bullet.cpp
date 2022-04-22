#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(INFO tInfo, bool bIsScrew)
{
	m_tInfo.fX = tInfo.fX;
	m_tInfo.fY = tInfo.fY;
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 5.f;

	m_fAngle = 0.f;

	m_bIsScrew = bIsScrew;
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY--;

	if (m_bIsScrew)
	{
		m_fAngle += m_fSpeed;
		m_tInfo.fX += ((m_tInfo.fCX - 15.f) * sinf(RADIAN * m_fAngle));
		m_tInfo.fY -= ((m_tInfo.fCY - 15.f) * cosf(RADIAN * m_fAngle));
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
}
