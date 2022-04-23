#include "stdafx.h"
#include "Life.h"


CLife::CLife()
{
}


CLife::~CLife()
{
}

void CLife::Initialize(void)
{

}

int CLife::Update(void)
{
	return 0;
}

void CLife::Late_Update(void)
{
}

void CLife::Render(HDC hDC)
{

	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 128, 0));
	HGDIOBJ h_old_pen = SelectObject(hDC, pen);

	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.fX -20, (int)m_tInfo.fY);
	LineTo(hDC, (int)m_tInfo.fX -20, (int)m_tInfo.fY+30);
	LineTo(hDC, (int)m_tInfo.fX , (int)m_tInfo.fY + 50);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY);
	LineTo(hDC, (int)m_tInfo.fX + 20, (int)m_tInfo.fY);
	LineTo(hDC, (int)m_tInfo.fX + 20, (int)m_tInfo.fY + 30);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 50);

	SelectObject(hDC, h_old_pen);

	DeleteObject(pen);
}

void CLife::Release(void)
{
}
