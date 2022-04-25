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
	m_tInfo.fX = 500.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 70.f;
}

int CTree::Update(void)
{
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
	
	brush = CreateSolidBrush(RGB(0, 64, 0));
	h_old_brush = SelectObject(hDC, brush);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
	

	brush = CreateSolidBrush(RGB(119, 80, 51));
	h_old_brush = SelectObject(hDC, brush);

	Rectangle(hDC, m_tRect.left -20, m_tRect.top + 50, m_tRect.right-20, m_tRect.bottom +50);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);

}

void CTree::Release(void)
{
}
