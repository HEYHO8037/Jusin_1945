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

	m_tInfo.fCX = 500.f;
	m_tInfo.fCY = 80.f;
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
	
}

void CMonsterHp::Render(HDC hDC)
{
	if (!m_pObj || 0 >= m_pObj->GetHP())
	{
		m_bDead = true;
		return;
	}

	HBRUSH	brush;
	HGDIOBJ h_old_brush;

	Update_Rect();
	m_barRight = m_tRect.left + (m_tInfo.fCX * ((float)m_pObj->GetHP() / m_pObj->GetMaxHP()));

	brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 0, 0));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, (int)m_barRight, m_tRect.bottom);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);

	if (250 < m_pObj->GetHP() && 500 >= m_pObj->GetHP())
	{
		Update_Rect();

		m_barRight = m_tRect.left + (m_tInfo.fCX * ((float)m_pObj->GetHP() / m_pObj->GetMaxHP()));

		brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		brush = CreateSolidBrush(RGB(255, 128, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, (int)m_barRight, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
	}
	if (250 >= m_pObj->GetHP())
	{
		Update_Rect();

		m_barRight = m_tRect.left + (m_tInfo.fCX * ((float)m_pObj->GetHP() / m_pObj->GetMaxHP()));

		brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		brush = CreateSolidBrush(RGB(255, 255, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, (int)m_barRight, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
	}
}

void CMonsterHp::Release(void)
{
}
