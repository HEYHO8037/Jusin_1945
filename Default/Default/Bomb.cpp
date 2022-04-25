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

	if (m_pObj->GetHP() <= 0)
	{
		m_bDead = true;

		return;
	}

	int iTempNum = *dynamic_cast<CPlayer*>(m_pObj)->GetBombNum();
	int iTemp = 0;
	if (3 >= iTempNum)
	{
		for (int i = 0; i < iTempNum; ++i)
		{

			HBRUSH	brush;
			HGDIOBJ h_old_brush;
			brush = CreateSolidBrush(RGB(128, 128, 255));
			h_old_brush = SelectObject(hDC, brush);

			Rectangle(hDC, m_tRect.left, m_tRect.top + iTemp, m_tRect.right, m_tRect.bottom + iTemp);
			Ellipse(hDC, m_tRect.right - 30, m_tRect.top + iTemp, m_tRect.right + 30, m_tRect.bottom + iTemp);
			Rectangle(hDC, m_tRect.left, m_tRect.top + iTemp, m_tRect.right, m_tRect.bottom + iTemp);
			
			SelectObject(hDC, h_old_brush);
			DeleteObject(brush);

			iTemp += 50;
		}
	}
	
}

void CBomb::Release(void)
{
}
