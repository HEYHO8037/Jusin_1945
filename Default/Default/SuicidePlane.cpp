#include "stdafx.h"
#include "SuicidePlane.h"


CSuicidePlane::CSuicidePlane()
{
}


CSuicidePlane::~CSuicidePlane()
{
	Release();
}

void CSuicidePlane::Initialize()
{
	//비행기 처음 위치 왼쪽부터 시작
	m_tInfo.fX = WINCX - 200.f;
	m_tInfo.fY = WINCY * 0.5f;
	//비행기 사이즈
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 8.f;
}


void CSuicidePlane::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CSuicidePlane::Release()
{
}

void CSuicidePlane::BehaviorEnter()
{
	
	switch (currentState)
	{
	//입장할때 플레이어 좌표 얻어오기, 임시로 설정
	case Create:
		
		targetPosition.x = WINCX / 2 + 200;
		targetPosition.y = WINCY / 2;

		originPosition.x = targetPosition.x;
		originPosition.y = targetPosition.y;
		break;

	case Pattern:
	{

		int angle = 90;
		Fire(angle);

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

	case Pattern:
		behaviorState = Exit;
		break;

	case Leave:
		m_tInfo.fY += m_fSpeed;
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

		behaviorState = Enter;
	}
}
