#include "stdafx.h"
#include "SuicidePlane.h"


CSuicidePlane::CSuicidePlane()
	:m_pPlayerInfo(nullptr), m_fDiagonal(0.f)
{
}


CSuicidePlane::~CSuicidePlane()
{
	Release();
}

void CSuicidePlane::Initialize()
{
	//비행기 사이즈
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 1.f;

	m_iMaxHP = 1;
	m_iHP = 1;

	m_iScore = 100;

}


void CSuicidePlane::Render(HDC hDC)
{
	HBRUSH	brush = CreateSolidBrush(RGB(157, 0, 0));
	HGDIOBJ h_old_brush = SelectObject(hDC, brush);
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(104, 0, 0));
	HGDIOBJ h_old_pen = SelectObject(hDC, pen);
	Ellipse(hDC, m_tRect.left, m_tRect.top + 30, m_tRect.right, m_tRect.bottom + 20);
	Ellipse(hDC, m_tRect.left - 40, m_tRect.top + 35, m_tRect.right + 40, m_tRect.bottom - 35);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	SelectObject(hDC, h_old_brush);
	SelectObject(hDC, h_old_pen);

	DeleteObject(brush);
	DeleteObject(pen);
}

void CSuicidePlane::Release()
{
}

void CSuicidePlane::CollisionEnter(CObj * _sour)
{
}

void CSuicidePlane::BehaviorEnter()
{
	if (!m_targetObj)
	{
		return;
	}
	switch (currentState)
	{
	//입장할때 플레이어 좌표 얻어오기, 임시로 설정
	case Create:
		targetPosition.x = appearPosition.x;
		targetPosition.y = appearPosition.y;
		break;

	case Pattern: {
		float width = fabs(m_targetObj->Get_Info().fX - m_tInfo.fX);
		float height = fabs(m_targetObj->Get_Info().fY - m_tInfo.fY);

		m_fDiagonal = sqrtf((width * width) + (height * height));
		m_fAngle = asinf(height / m_fDiagonal);

		m_tDir.fX = cosf(m_fAngle);
		m_tDir.fY = sinf(m_fAngle);

		if (m_tInfo.fX > m_targetObj->Get_Info().fX) {
			m_tDir.fX *= -1;
		}

		m_fSpeed = 8.f;
	}
		break;

	case Destroy :
		m_bDead = true;
		break;
	}

	behaviorState = Execute;
}

void CSuicidePlane::BehaviorExecute()
{
	switch (currentState)
	{
	case Create:
		if (TargetMove()) {
			
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern: {
		m_tInfo.fX += m_fSpeed * m_tDir.fX; 
		m_tInfo.fY += m_fSpeed * m_tDir.fY; 

		Update_Rect();
		LeaveCheck();
	}
		break;

	case Leave:
		
		m_tInfo.fX += (m_fDiagonal) * m_fAngle;
		m_tInfo.fY += (m_fDiagonal) * m_fAngle;
		LeaveCheck();
		break;

	}
}

void CSuicidePlane::BehaviorExit()
{

	switch (currentState)
	{
	case Create:
		currentState = Pattern;
		break;

	case Pattern:
		currentState = Leave;
		break;

	case Leave:
		break;

	}
	
	behaviorState = Enter;
}
