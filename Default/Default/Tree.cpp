#include "stdafx.h"
#include "Tree.h"


CTree::CTree()
{
}


CTree::~CTree()
{
}

void CTree::Initialize(void)
{
	m_tInfo.fX = 550.f;
	m_tInfo.fY = 350.f;

	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 0.2f;
}

int CTree::Update(void)
{

	m_tInfo.fY += m_fSpeed;

	if (1024 < m_tRect.top)
	{
		m_tInfo.fX = float((rand() % 50 + 10)*(rand() % 12 + 1)) + 40.f;
		m_tInfo.fY = float(((-rand() % 10 + 1) * 15) - 10);

	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CTree::Late_Update(void)
{

	
}

void CTree::Render(HDC hDC)
{


	HBRUSH	brush;
	HGDIOBJ h_old_brush;
	HPEN pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	HGDIOBJ h_old_pen = SelectObject(hDC, pen);

	brush = CreateSolidBrush(RGB(119, 60, 51));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left+20, m_tRect.top + 60, m_tRect.right+30, m_tRect.bottom +20 );
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(119, 60, 51));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left -30, m_tRect.top + 70, m_tRect.right -20, m_tRect.bottom + 30);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(119, 60, 51));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left+20, m_tRect.top + 50, m_tRect.right-20, m_tRect.bottom +80);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(0, 64, 0));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(0, 64, 0));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left+60, m_tRect.top+45, m_tRect.right+40, m_tRect.bottom+30);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(0, 64, 0));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, m_tRect.left -30, m_tRect.top + 60, m_tRect.right - 55, m_tRect.bottom + 45);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
	SelectObject(hDC, h_old_pen);
	DeleteObject(pen);
}

void CTree::Release(void)
{
}
