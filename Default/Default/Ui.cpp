#include "stdafx.h"
#include "Ui.h"


CUi::CUi()
	:m_fSpeed(0.f), m_bDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CUi::~CUi()
{
}

void CUi::Update_Rect(void)
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5));
}
