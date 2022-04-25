#include "stdafx.h"
#include "Item.h"




CItem::CItem() : m_Item_Id(ITEM_END), m_iCount(0)
{
}


CItem::~CItem()
{

}

void CItem::Initialize(void)
{

	//m_Font = CreateFont()
	srand((unsigned int)time(NULL));
	m_Item_Id = (ITEMID)(rand()% ITEM_END); 
	m_tInfo.fCX = (float)PlayerSize - 10;  
	m_tInfo.fCY = (float)PlayerSize - 10;
	m_fSpeed = 5.f;
	m_fAngle = -((rand() % 50) + 31);
	m_ItemPoint.x = 1;
	m_ItemPoint.y = -1;
	rc_Dead = m_tRect;
}

int CItem::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (0 > m_tRect.left || WINCX < m_tRect.right)
	{
		++m_iCount; // 튕긴 횟수 증가
		m_ItemPoint.x *= -1;
	}
	if (0 > m_tRect.bottom || WINCY < m_tRect.top)
	{
		++m_iCount; // 튕긴 횟수 증가
		m_ItemPoint.y *= -1;
	}
	 
	if (5<= m_iCount) // 튕긴 횟수 체크
	{
		m_bDead = true;
		return OBJ_DEAD;
	}

	m_tInfo.fX += (m_ItemPoint.x * m_fSpeed )  * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY += (m_ItemPoint.y * m_fSpeed) * sinf((m_fAngle * PI) / 180.f);
	
	
	


	/*if (GetAsyncKeyState(VK_LEFT))
		m_fAngle -= 5.f;

	if (GetAsyncKeyState(VK_RIGHT))
		m_fAngle += 5.f;

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX += -m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= -m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}*/

	//m_tInfo.fX += m_fSpeed;
	//m_tInfo.fY += m_fSpeed;
	
	/*if (100 < m_tRect.left || WINCX - 100 > m_tRect.right)
	{
		m_tInfo.fX -= m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY += m_fSpeed * sinf((m_fAngle * PI) / 180.f);


	}
	else if (WINCY - 100 <= m_tRect.bottom || 100 >= m_tRect.top)
	{
		m_tInfo.fX -= m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY += m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}*/
	/*m_tInfo.fX -= m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY += m_fSpeed * sinf((m_fAngle * PI) / 180.f);*/


	Update_Rect();
	rc.bottom = m_tRect.bottom;
	rc.left = m_tRect.left;
	rc.right = m_tRect.right;
	rc.top = m_tRect.top + 15;
	
	return OBJ_NOEVENT;

}

void CItem::Late_Update(void)
{


}

void CItem::Render(HDC hDC)
{
	Item_Render(hDC);
}

void CItem::Release(void)
{



}

void CItem::CollisionEnter(CObj * _sour)
{
	m_bDead = true;


}

void CItem::Item_Render(HDC hDC)
{
#pragma region Render

	
	HBRUSH	brush;
	HGDIOBJ h_old_brush;
	HPEN pen;
	HGDIOBJ h_old_pen;

	
	switch (m_Item_Id)
	{
	case ITEM_POWER:
		brush = CreateSolidBrush(RGB(255, 255, 051));
		pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 051));
		h_old_brush = SelectObject(hDC, brush);
		h_old_pen = SelectObject(hDC, pen);
		
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		
		SelectObject(hDC, h_old_brush);
		SelectObject(hDC, h_old_pen);
		DeleteObject(brush);
		DeleteObject(pen);
		//lstrcpy(m_szItem_Name, L"P");
		
		
			break;
	case ITEM_SHIELD:
		brush = CreateSolidBrush(RGB(051, 051, 153));
		pen = CreatePen(PS_SOLID, 1, RGB(051,051,153));
		h_old_brush = SelectObject(hDC, brush);
		h_old_pen = SelectObject(hDC, pen);
		
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		
		SelectObject(hDC, h_old_brush);
		SelectObject(hDC, h_old_pen);
		DeleteObject(brush);
		DeleteObject(pen);
		//lstrcpy(m_szItem_Name, L"S");
		//SetBkColor(hDC, 0x999999);
		
		break;
	case ITEM_BOMB:
		brush = CreateSolidBrush(RGB(204, 0, 0));
		pen = CreatePen(PS_SOLID, 1, RGB(204, 0, 0));
		h_old_brush = SelectObject(hDC, brush);
		h_old_pen = SelectObject(hDC, pen);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		
		SelectObject(hDC, h_old_brush);
		SelectObject(hDC, h_old_pen);
		DeleteObject(brush);
		DeleteObject(pen);
		//lstrcpy(m_szItem_Name, L"B");
		
		break;
	case ITEM_END:
		return;
	}

	/*if (8 > m_iCount)
	{*/
	if (false == m_bDead)
	{

		brush = CreateSolidBrush(RGB(0, 0, 200));
		h_old_brush = SelectObject(hDC, brush);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 37, m_tRect.bottom - 32);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 32, m_tRect.bottom - 37);

		Rectangle(hDC, m_tRect.left + 37, m_tRect.top, m_tRect.right + 1, m_tRect.bottom - 32);
		Rectangle(hDC, m_tRect.left + 32, m_tRect.top, m_tRect.right + 1, m_tRect.bottom - 37);

		Rectangle(hDC, m_tRect.left, m_tRect.top + 32, m_tRect.right - 37, m_tRect.bottom);
		Rectangle(hDC, m_tRect.left, m_tRect.top + 37, m_tRect.right - 32, m_tRect.bottom);

		Rectangle(hDC, m_tRect.left + 37, m_tRect.top + 32, m_tRect.right + 1, m_tRect.bottom);
		Rectangle(hDC, m_tRect.left + 32, m_tRect.top + 37, m_tRect.right + 1, m_tRect.bottom);

		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);

		//DrawText(hDC, m_szItem_Name, lstrlen(m_szItem_Name), &rc, DT_CENTER);


		/*HPEN m_pen2 = CreatePen(PS_SOLID, 3, RGB(153, 153, 153));
		HBRUSH m_brush = CreateSolidBrush(RGB(0, 0, 200));*/

		/*
		Delete Item
		HBRUSH m_brush_temp = CreateSolidBrush(RGB(255, 255, 255));
		HPEN m_pen_temp = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		SelectObject(hDC, m_brush_temp);
		SelectObject(hDC, m_pen_temp);

			Ellipse(hDC, rc_Dead.left, rc_Dead.top, rc_Dead.right, rc_Dead.bottom);

			rc_Dead.left -= 2;  rc_Dead.top -= 2;
			rc_Dead.right += 2, rc_Dead.bottom += 2;
		
			DeleteObject(m_brush_temp);
			DeleteObject(m_pen_temp);*/

		}
		
	else
	{

		// pen = CreatePen(PS_SOLID, 3, RGB(153, 153, 153));
		// brush = CreateSolidBrush(RGB(0, 0, 200));
		//
		//DeleteObject(pen);
		//DeleteObject(brush);
		

	}



		
	
	//else if(8 == m_iCount)
	//{
	//	//Line
	//}

	
	
}

ITEMID CItem::GetItemID() const
{
	if (this)
	{
		return m_Item_Id;
	}
	else
	{
		return ITEM_END;
	}
}
