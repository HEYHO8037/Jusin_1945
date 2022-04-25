#include "stdafx.h"
#include "Life.h"
#include "Player.h"

CLife::CLife()
{
}


CLife::~CLife()
{
	m_tInfo.fX = 50.f;
	m_tInfo.fY = 930.f;
}

void CLife::Initialize(void)
{
	Release();
}

int CLife::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	//if (0 >= m_pObj->GetHP())
	//{
	//	m_bDead = true;
	//}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CLife::Late_Update(void)
{

}

void CLife::Render(HDC hDC)
{
	int iTemp = 0;

	if (!m_pObj)
		return;

	if (m_pObj->GetHP() > 0)
	{
		//플레이어 완전사망시 주소값 못불러와서 에러
		for (int i = 0; i < *dynamic_cast<CPlayer*>(m_pObj)->GetLife(); ++i)
		{

			HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
			HGDIOBJ h_old_pen = SelectObject(hDC, pen);

			MoveToEx(hDC, (int)m_tInfo.fX + iTemp, (int)m_tInfo.fY, nullptr);
			LineTo(hDC, (int)m_tInfo.fX - 20 + iTemp, (int)m_tInfo.fY);
			LineTo(hDC, (int)m_tInfo.fX - 20 + iTemp, (int)m_tInfo.fY + 30);
			LineTo(hDC, (int)m_tInfo.fX + iTemp, (int)m_tInfo.fY + 50);
			LineTo(hDC, (int)m_tInfo.fX + iTemp, (int)m_tInfo.fY);
			LineTo(hDC, (int)m_tInfo.fX + 20 + iTemp, (int)m_tInfo.fY);
			LineTo(hDC, (int)m_tInfo.fX + 20 + iTemp, (int)m_tInfo.fY + 30);
			LineTo(hDC, (int)m_tInfo.fX + iTemp, (int)m_tInfo.fY + 50);

			SelectObject(hDC, h_old_pen);
			DeleteObject(pen);

			Update_Rect();
			iTemp += 70;
		}
	}

	

	}

void CLife::Release(void)
{
}
