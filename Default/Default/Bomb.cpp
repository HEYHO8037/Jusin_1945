#include "stdafx.h"
#include "Bomb.h"


CBomb::CBomb()
{
}


CBomb::~CBomb()
{
}

void CBomb::Initialize(void)
{

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
}

int CBomb::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBomb::Late_Update(void)
{
}

void CBomb::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	Ellipse(hDC, m_tRect.right - 30, m_tRect.top, m_tRect.right + 30, m_tRect.bottom); 
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tRect.left, m_tRect.top + 10, nullptr);       
	LineTo(hDC, m_tRect.left - 10, m_tRect.top);
	LineTo(hDC, m_tRect.left - 25, m_tRect.top);
	LineTo(hDC, m_tRect.left - 25, m_tRect.bottom);
	LineTo(hDC, m_tRect.left - 10, m_tRect.bottom);
	LineTo(hDC, m_tRect.left, m_tRect.bottom - 10);
}

void CBomb::Release(void)
{
}
