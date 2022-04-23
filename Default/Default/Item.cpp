#include "stdafx.h"
#include "Item.h"


CItem::CItem() : m_Item_Id(ITEM_END)
{
}


CItem::~CItem()
{

}

void CItem::Initialize(void)
{
	Set_pos(200.f, 300.f); // 임시 위치 지정 (몬스터와 연계)
	srand((unsigned int)time(NULL));
	m_Item_Id = (ITEMID)(rand()% ITEM_END); // 랜덤하게 아이템 드롭
	//m_Item_Id = ITEM_POWER;
	m_tInfo.fCX = (float)PlayerSize - 10; // 사각형 크기 -플레이어 크기랑 몹 크기에 맞게 임의 조정 예정
	m_tInfo.fCY = (float)PlayerSize - 10;
	m_fSpeed = 5.f;
	//m_fAngle = 90.f;
	
}

int CItem::Update(void)
{
	m_tInfo.fY += m_fSpeed;
	
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
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
	{
		m_fSpeed *= -1.f;
		m_fAngle += 30.f;
		
		
	}
		
	if (WINCY - 100 <= m_tRect.bottom || 100 >= m_tRect.top)
	{
		m_fSpeed *= -1.f;
		m_fAngle += 30.f;
	}
		
	
}

void CItem::Render(HDC hDC)
{
	Item_Render(hDC);
}

void CItem::Release(void)
{

}

void CItem::Item_Render(HDC hDC)
{
#pragma region 아이템 모양
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//Ellipse(hDC, m_tRect.right - 30, m_tRect.top, m_tRect.right + 30, m_tRect.bottom); // 둥근 머리
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//MoveToEx(hDC, m_tRect.right, m_tRect.top,nullptr); // 아이템 머리(삼각형)
	//LineTo(hDC, m_tRect.right + 30, m_tRect.top + 30); 
	//LineTo(hDC, m_tRect.right, m_tRect.bottom);
	//
	//MoveToEx(hDC, m_tRect.left, m_tRect.top + 10, nullptr); //아이템 꼬리
	//LineTo(hDC, m_tRect.left - 20, m_tRect.top);
	//LineTo(hDC, m_tRect.left - 35, m_tRect.top);
	//LineTo(hDC, m_tRect.left - 35, m_tRect.bottom);
	//LineTo(hDC, m_tRect.left - 20, m_tRect.bottom);
	//LineTo(hDC, m_tRect.left, m_tRect.bottom - 10);


	/*MoveToEx(hDC, m_tRect.left, m_tRect.top, nullptr);
	LineTo(hDC, m_tRect.left - 15, m_tRect.top - 20);
	LineTo(hDC, m_tRect.left - 60, m_tRect.top - 20);
	LineTo(hDC, m_tRect.left -45, m_tRect.top);*/
	//LineTo(hDC, m_tRect.left - 45, m_tRect.bottom); // 도안 1
#pragma endregion 아이템 모양

	switch (m_Item_Id)
	{
	case ITEM_POWER:

		HBRUSH brush;
		HPEN pen;
		pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		brush = CreateSolidBrush(RGB(0, 0, 200));
		SelectObject(hDC, pen);
		SelectObject(hDC, brush);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 35, m_tRect.bottom - 30); //좌.상
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 30, m_tRect.bottom - 35);

		Rectangle(hDC, m_tRect.left + 35, m_tRect.top, m_tRect.right, m_tRect.bottom - 30); // 우.상
		Rectangle(hDC, m_tRect.left + 30, m_tRect.top, m_tRect.right, m_tRect.bottom - 35);

		Rectangle(hDC, m_tRect.left, m_tRect.top + 30, m_tRect.right - 35, m_tRect.bottom); // 좌.하
		Rectangle(hDC, m_tRect.left, m_tRect.top + 35, m_tRect.right - 30, m_tRect.bottom);

		Rectangle(hDC, m_tRect.left + 35, m_tRect.top + 30, m_tRect.right, m_tRect.bottom); //우.하
		Rectangle(hDC, m_tRect.left + 30, m_tRect.top + 35, m_tRect.right, m_tRect.bottom);

		DeleteObject(pen);
		DeleteObject(brush);


		lstrcpy(m_szItem_Name, L"P");
		DrawText(hDC, m_szItem_Name, lstrlen(m_szItem_Name), &rc, DT_CENTER);
			break;
	case ITEM_SHIELD:
		HBRUSH brush2;
		HPEN pen2;
		pen2 = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		brush2 = CreateSolidBrush(RGB(0, 0, 200));
		SelectObject(hDC, pen2);
		SelectObject(hDC, brush2);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 35, m_tRect.bottom - 30);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 30, m_tRect.bottom - 35);

		Rectangle(hDC, m_tRect.left + 35, m_tRect.top, m_tRect.right, m_tRect.bottom - 30);
		Rectangle(hDC, m_tRect.left + 30, m_tRect.top, m_tRect.right, m_tRect.bottom - 35);

		Rectangle(hDC, m_tRect.left, m_tRect.top + 30, m_tRect.right - 35, m_tRect.bottom);
		Rectangle(hDC, m_tRect.left, m_tRect.top + 35, m_tRect.right - 30, m_tRect.bottom);

		Rectangle(hDC, m_tRect.left + 35, m_tRect.top + 30, m_tRect.right, m_tRect.bottom);
		Rectangle(hDC, m_tRect.left + 30, m_tRect.top + 35, m_tRect.right, m_tRect.bottom);

		DeleteObject(pen2);
		DeleteObject(brush2);
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		lstrcpy(m_szItem_Name, L"S");
		DrawText(hDC, m_szItem_Name, lstrlen(m_szItem_Name), &rc, DT_CENTER);
		break;
	case ITEM_BOMB:
		
		HBRUSH brush3;
		HPEN pen3;
		pen3 = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		brush3 = CreateSolidBrush(RGB(0, 0, 200));
		SelectObject(hDC, pen3);
		SelectObject(hDC, brush3);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 35, m_tRect.bottom - 30);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 30, m_tRect.bottom - 35);

		Rectangle(hDC, m_tRect.left + 35, m_tRect.top, m_tRect.right, m_tRect.bottom - 30);
		Rectangle(hDC, m_tRect.left + 30, m_tRect.top, m_tRect.right, m_tRect.bottom - 35);

		Rectangle(hDC, m_tRect.left, m_tRect.top + 30, m_tRect.right - 35, m_tRect.bottom);
		Rectangle(hDC, m_tRect.left, m_tRect.top + 35, m_tRect.right - 30, m_tRect.bottom);

		Rectangle(hDC, m_tRect.left + 35, m_tRect.top + 30, m_tRect.right, m_tRect.bottom);
		Rectangle(hDC, m_tRect.left + 30, m_tRect.top + 35, m_tRect.right, m_tRect.bottom);

		DeleteObject(pen3);
		DeleteObject(brush3);
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		lstrcpy(m_szItem_Name, L"B");
		DrawText(hDC, m_szItem_Name, lstrlen(m_szItem_Name), &rc, DT_CENTER);
		break;
	case ITEM_END:
		return;
	}

}
