#include "stdafx.h"
#include "MonsterHp.h"


CMonsterHp::CMonsterHp()
{
}


CMonsterHp::~CMonsterHp()
{
}

void CMonsterHp::Initialize(void)
{
	m_tInfo.fX = WINCX * 0.5f;
	m_tInfo.fY = 120.f;

	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 100.f;
}

int CMonsterHp::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonsterHp::Late_Update(void)
{
	m_tInfo.fCX -= 50.f;
	
	Update_Rect();

	m_bDead = true;
}

void CMonsterHp::Render(HDC hDC)
{

	HBRUSH	brush;
	HPEN pen;
	HGDIOBJ h_old_pen;
	HGDIOBJ h_old_brush;

	pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	h_old_pen = SelectObject(hDC, pen);

	brush = CreateSolidBrush(RGB(255,38, 38));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left-150, m_tRect.top + 10, m_tRect.right+150, m_tRect.bottom - 10);
	SelectObject(hDC, h_old_brush);

	DeleteObject(brush);
	DeleteObject(pen);

}

void CMonsterHp::Release(void)
{
}
