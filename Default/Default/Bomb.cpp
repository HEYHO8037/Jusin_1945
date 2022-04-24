#include "stdafx.h"
#include "Bomb.h"
#include "Player.h"

CBomb::CBomb()
{
}


CBomb::~CBomb()
{
}

void CBomb::Initialize(void)
{
	m_tInfo.fX = 70.f;
	m_tInfo.fY = 550.f;
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
	int iTempNum = *dynamic_cast<CPlayer*>(m_pObj)->GetBombNum();
	int iTemp = 0;
	if (3 >= iTempNum)
	{
		for (int i = 0; i < iTempNum; ++i)
		{
			Rectangle(hDC, m_tRect.left, m_tRect.top + iTemp, m_tRect.right, m_tRect.bottom + iTemp);

			Ellipse(hDC, m_tRect.right - 30, m_tRect.top + iTemp, m_tRect.right + 30, m_tRect.bottom + iTemp);
			Rectangle(hDC, m_tRect.left, m_tRect.top + iTemp, m_tRect.right, m_tRect.bottom + iTemp);
			MoveToEx(hDC, m_tRect.left, m_tRect.top + 10 + iTemp, nullptr);
			LineTo(hDC, m_tRect.left - 10, m_tRect.top + iTemp);
			LineTo(hDC, m_tRect.left - 25, m_tRect.top + iTemp);
			LineTo(hDC, m_tRect.left - 25, m_tRect.bottom + iTemp);
			LineTo(hDC, m_tRect.left - 10, m_tRect.bottom + iTemp);
			LineTo(hDC, m_tRect.left, m_tRect.bottom - 10 + iTemp);

			iTemp += 50;
		}
	}
	
}

void CBomb::Release(void)
{
}
