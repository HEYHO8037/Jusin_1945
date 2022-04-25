#include "stdafx.h"
#include "Plane2.h"


CPlane2::CPlane2():
	shotTimer(nullptr) {
}


CPlane2::~CPlane2() {
	Release();
}

void CPlane2::Initialize() {
	m_tInfo.fCX = 130; //50
	m_tInfo.fCY = 80; 

	m_fSpeed = 5.f;

	m_iScore = 100;

	m_iMaxHP = 1;
	m_iHP = 1;
};

void CPlane2::Render(HDC hDC) {
	HBRUSH brush;
	HGDIOBJ OldBrush;

	EffectRender();

	brush = CreateSolidBrush(RGB(10, 255, 10));
	OldBrush = SelectObject(hDC, brush);

	DisplayInfo(hDC, currentState);

	Ellipse(hDC, m_tRect.left + 50, m_tRect.top + 45, m_tRect.right - 50, m_tRect.bottom + 35);
	Ellipse(hDC, m_tRect.left, m_tRect.top + 25, m_tRect.right, m_tRect.bottom - 25); // Wing

	Ellipse(hDC, m_tRect.left + 25, m_tRect.top  , m_tRect.right - 25, m_tRect.bottom - 80);

	Rectangle(hDC, m_tRect.left + 50, m_tRect.top, m_tRect.right - 50, m_tRect.bottom);

	SelectObject(hDC, OldBrush);
	DeleteObject(brush);

	DisplayInfo(hDC, currentState);
};

void CPlane2::Release() {
	if (shotTimer)
		Safe_Delete<CTimer*>(shotTimer);
};

void CPlane2::BehaviorEnter() {
	switch (currentState) {
	case Create:
		targetPosition.x = appearPosition.x;
		targetPosition.y = appearPosition.y;
		break;

	case Pattern1: {
		shotTimer = new CTimer;
		float dirAngle = appearPosition.x > (WINCX * 0.5f) ? 80 : -80;
		m_tDir.fX = cosf((90 + dirAngle) * RADIAN);
		m_tDir.fY = 0.2f;

		shotTimer->StartTimer(0.5f, [&]() {
			Fire(90);
		});
	}
	break;

	}

	behaviorState = Execute;
} 
void CPlane2::BehaviorExecute() {
	switch (currentState) {
	case Create:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern1:
		m_tInfo.fX += m_fSpeed * m_tDir.fX;
		m_tInfo.fY += m_fSpeed * m_tDir.fY;
		shotTimer->Update();

		LeaveCheck();
		break;
	}
} 

void CPlane2::BehaviorExit() {
	switch (currentState) {
	case Create:
		currentState = Pattern1;
		break;

	case Pattern1:
		break;
	}

	behaviorState = Enter;
} 