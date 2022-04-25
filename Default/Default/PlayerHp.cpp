#include "stdafx.h"
#include "PlayerHp.h"

CPlayerHp::CPlayerHp()
	:m_pPlayerInfo(nullptr)
{
}


CPlayerHp::~CPlayerHp()
{
	Release();
}

void CPlayerHp::Initialize(void)
{
	m_tInfo.fX = 400;
	m_tInfo.fY = 630;
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 12.f;
}

int CPlayerHp::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	if (m_pPlayerInfo->fCX <= 0)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX = m_pPlayerInfo->fX;
	m_tInfo.fY = m_pPlayerInfo->fY - 45;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayerHp::Late_Update(void)
{

}

void CPlayerHp::Render(HDC hDC)
{

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
	Rectangle(hDC, m_tRect.left, m_tRect.top, int(m_barRight), m_tRect.bottom);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);


	if(40 <= m_pObj->GetHP() && m_pObj->GetHP() < 75)
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
	
	if (40 > m_pObj->GetHP() && 0 <= m_pObj->GetHP())
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

void CPlayerHp::Release(void)
{
}
