#include "stdafx.h"
#include "Barrier.h"


CBarrier::CBarrier()
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
}

void CBarrier::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBarrier::Release(void)
{
	m_pPlayerInfo = nullptr;
}

void CBarrier::SetPlayerInfo(INFO * pPlayerInfo)
{
	m_pPlayerInfo = pPlayerInfo;

	m_tInfo.fX = m_pPlayerInfo->fX;
	m_tInfo.fY = m_pPlayerInfo->fY;
}

void CBarrier::UpdatePos()
{
	m_tInfo.fX = m_pPlayerInfo->fX;
	m_tInfo.fY = m_pPlayerInfo->fY;
}
