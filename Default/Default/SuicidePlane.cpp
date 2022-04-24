#include "stdafx.h"
#include "SuicidePlane.h"


CSuicidePlane::CSuicidePlane()
	:m_pPlayerInfo(nullptr)
{
}


CSuicidePlane::~CSuicidePlane()
{
	Release();
}

void CSuicidePlane::Initialize()
{
	//����� ó�� ��ġ ���ʺ��� ����
	m_tInfo.fX = -50.f;
	m_tInfo.fY = 40.f;
	//����� ������
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 0.3f;

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
	//�����Ҷ� �÷��̾� ��ǥ ������, �ӽ÷� ����
	case Create:
		
		targetPosition.x = 45;
		targetPosition.y = 50;

		break;

	case Pattern:
		m_fSpeed = 6.f;
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
		//x,y��ǥ�� player���� �޾ƿ°��ֱ�
		//m_tInfo.fX = m_pPlayerInfo->fX;
		//m_tInfo.fY = m_pPlayerInfo->fY;
		m_tInfo.fX += m_fSpeed;
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

	}
	
	behaviorState = Enter;
}
