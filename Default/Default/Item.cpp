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
	Set_pos(400.f, 300.f); 
	srand((unsigned int)time(NULL));
	m_Item_Id = (ITEMID)(rand()% ITEM_END); 
	m_Item_Id = ITEM_SHIELD;
	m_tInfo.fCX = (float)PlayerSize - 10;  
	m_tInfo.fCY = (float)PlayerSize - 10;
	//m_fSpeed = 5.f;
	m_fAngle = -90.f;
	m_ItemPoint.x = 1;
	m_ItemPoint.y = -1;
	
}

int CItem::Update(void)
{
	
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
	
	return 0;
}

void CItem::Late_Update(void)
{
	 
	if ((0 <= m_tRect.left && WINCX  >= m_tRect.right)
		&& m_tRect.bottom >= WINCY ) //Down_Wall
	{
		m_ItemPoint.y *= -1;
		if ((m_ItemPoint.x = -1) && m_fAngle == -90.f)
		{
			m_fAngle += 45.f;

		}
		else if(m_fAngle == -90.f)
		{
			m_fAngle -= 45.f;
		}
		else
		{
			if (m_ItemPoint.x = -1)
			{

			}
				//m_fAngle -= 90.f;
			else
			{

			}
				//m_fAngle += 90.f;
		}
		m_iCount += 1;
	}
	if (( 0 <= m_tRect.top && WINCY  >= m_tRect.bottom)
		&& m_tRect.right >= WINCX ) //Right_Wall
	{
		m_fAngle += 45.f;
		m_iCount += 1;

	}

	if ((0 <= m_tRect.left && WINCX  >= m_tRect.right)
		&& m_tRect.top <= 0) // Up_Wall
	{
		m_ItemPoint.y *= -1;
		if (m_ItemPoint.x == 1)
		{
			m_fAngle -= 90.f;
			m_iCount += 1;

		}
			
		else
		{
			m_iCount += 1;
		}
	}

	if ((0 <= m_tRect.top && WINCY  >= m_tRect.bottom)
		&& m_tRect.left <= 0) // Left_Wall
	{
		m_ItemPoint.x *= -1;
		if (m_ItemPoint.x = -1)
		{
			m_fAngle -= 90.f;
			m_iCount += 1;

		}
		else
		{
			
			m_iCount += 1;


		}
	}
		
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
}

void CItem::Item_Render(HDC hDC)
{
#pragma region Render


	//MoveToEx(hDC, m_tRect.right, m_tRect.top,nullptr); // ������ �Ӹ�(�ﰢ��)
	//LineTo(hDC, m_tRect.right + 30, m_tRect.top + 30); 
	//LineTo(hDC, m_tRect.right, m_tRect.bottom);
	//

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// Bomb UI
	//Ellipse(hDC, m_tRect.right - 30, m_tRect.top, m_tRect.right + 30, m_tRect.bottom); // �ձ� �Ӹ�
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//MoveToEx(hDC, m_tRect.left, m_tRect.top + 10, nullptr);
	//LineTo(hDC, m_tRect.left - 35, m_tRect.top);
	//LineTo(hDC, m_tRect.left - 35, m_tRect.bottom);
	//LineTo(hDC, m_tRect.left - 20, m_tRect.bottom);
	//LineTo(hDC, m_tRect.left, m_tRect.bottom - 10);


	/*MoveToEx(hDC, m_tRect.left, m_tRect.top, nullptr);
	LineTo(hDC, m_tRect.left - 15, m_tRect.top - 20);
	LineTo(hDC, m_tRect.left - 60, m_tRect.top - 20);
	LineTo(hDC, m_tRect.left -45, m_tRect.top);*/
	//LineTo(hDC, m_tRect.left - 45, m_tRect.bottom); // ���� 1
#pragma endregion Render

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	/*lstrcpy(m_szItem_Name, L"S");
	TextOut(hDC, m_tRect.left + 15, m_tRect.top + 10, m_szItem_Name, lstrlen(m_szItem_Name));*/
	//DrawText(hDC, m_szItem_Name, lstrlen(m_szItem_Name), &rc, DT_CENTER);
	
	m_Item_Id = ITEM_SHIELD;
	
	switch (m_Item_Id)
	{
	case ITEM_POWER:
		m_pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 051));
		m_brush = CreateSolidBrush(RGB(255, 255, 051));
		//lstrcpy(m_szItem_Name, L"P");
		
		
			break;
	case ITEM_SHIELD:
		m_pen = CreatePen(PS_SOLID, 1, RGB(051,051,153));
		m_brush = CreateSolidBrush(RGB(051, 051, 153));
		//lstrcpy(m_szItem_Name, L"S");
		//SetBkColor(hDC, 0x999999);
		
		break;
	case ITEM_BOMB:
		m_pen = CreatePen(PS_SOLID, 1, RGB(204, 0, 0));
		m_brush = CreateSolidBrush(RGB(204, 0, 0));
		//lstrcpy(m_szItem_Name, L"B");
		
		break;
	case ITEM_END:
		return;
	}

	/*if (8 > m_iCount)
	{*/
		
		SelectObject(hDC, m_pen);
		SelectObject(hDC, m_brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		HPEN m_pen2 = CreatePen(PS_SOLID, 3, RGB(153,153,153));
		HBRUSH m_brush = CreateSolidBrush(RGB(0, 0, 200));
		SelectObject(hDC, m_pen2);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 37, m_tRect.bottom - 32); 
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 32, m_tRect.bottom - 37);

		Rectangle(hDC, m_tRect.left + 37, m_tRect.top, m_tRect.right + 1, m_tRect.bottom - 32); 
		Rectangle(hDC, m_tRect.left + 32, m_tRect.top, m_tRect.right + 1, m_tRect.bottom - 37);

		Rectangle(hDC, m_tRect.left, m_tRect.top + 32, m_tRect.right - 37, m_tRect.bottom); 
		Rectangle(hDC, m_tRect.left, m_tRect.top + 37, m_tRect.right - 32, m_tRect.bottom);

		Rectangle(hDC, m_tRect.left + 37, m_tRect.top + 32, m_tRect.right + 1, m_tRect.bottom); 
		Rectangle(hDC, m_tRect.left + 32, m_tRect.top + 37, m_tRect.right + 1, m_tRect.bottom);

		DrawText(hDC, m_szItem_Name, lstrlen(m_szItem_Name), &rc, DT_CENTER);



		
	
	//else if(8 == m_iCount)
	//{
	//	//Line
	//}
	DeleteObject(m_pen);
	DeleteObject(m_brush);

}
