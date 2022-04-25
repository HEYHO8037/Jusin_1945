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
	//비행기 처음 위치 왼쪽부터 시작
	m_tInfo.fX = -30.f;
	m_tInfo.fY = 40.f;
	//비행기 사이즈
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 0.3f;

	m_iMaxHP = 1;
	m_iHP = 1;

}


void CSuicidePlane::Render(HDC hDC)
{
	HBRUSH	brush = CreateSolidBrush(RGB(157, 0, 0));
	HGDIOBJ h_old_brush = SelectObject(hDC, brush);
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(104, 0, 0));
	HGDIOBJ h_old_pen = SelectObject(hDC, pen);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

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
	
	switch (currentState)
	{
	//입장할때 플레이어 좌표 얻어오기, 임시로 설정
	case Create:
		
		targetPosition.x = 20;
		targetPosition.y = 80;
	

		break;

	case Pattern:
	
		m_tDir.fX = fabs(targetObj->Get_Info().fX - targetPosition.x);
		m_tDir.fY = fabs(targetObj->Get_Info().fY - targetPosition.y);

		m_fDiagonal = sqrtf((targetPosition.x *m_tDir.fX) + (targetPosition.y *m_tDir.fY));
		m_fAngle = atan2(m_tDir.fY, m_tDir.fX);
		m_fSpeed = 8.f;
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

	case Pattern:

		m_tInfo.fX += m_fSpeed* cosf(m_fAngle);
		m_tInfo.fY += m_fSpeed* sinf(m_fAngle);

		//behaviorState = Exit;
		Update_Rect();
		break;

	case Leave:
		
		m_tInfo.fX += (m_fDiagonal) * m_fAngle;
		m_tInfo.fY += (m_fDiagonal)* m_fAngle;
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
