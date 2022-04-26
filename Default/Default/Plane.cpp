#include "stdafx.h"
#include "Plane.h"


CPlane::CPlane():
	shotInterval(5.f),
	residenceTimer(nullptr) {
}


CPlane::~CPlane() {
	Release();
}

void CPlane::Initialize() {
	m_tInfo.fX = WINCX + 200;
	m_tInfo.fY = WINCY / 2;

	m_tInfo.fCX = 150;
	m_tInfo.fCY = 100; 

	m_fSpeed = 5.f;

	m_iScore = 100;

	m_iMaxHP = 1;
	m_iHP = 1;

	residenceTimer = new CTimer;
};

void CPlane::Render(HDC hDC) {
	HBRUSH brush;
	HGDIOBJ OldBrush;

	EffectRender();

	brush = CreateSolidBrush(RGB(0, 0, 235));
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

void CPlane::Release() {
	if (residenceTimer)
		Safe_Delete<CTimer*>(residenceTimer);
};

void CPlane::BehaviorEnter() {
	switch (currentState) {
	case Create:
		targetPosition.x = appearPosition.x;
		targetPosition.y = appearPosition.y;

		originPosition.x = targetPosition.x;
		originPosition.y = targetPosition.y;
		break;

	case Pattern1: {
		Fire(baseShotAngle);
	}
	break;

	case Idle:
		residenceTimer->StartTimer(shotInterval, [&]() {
			behaviorState = Exit;
		});
		break;

	case Destroy:
		m_bDead = true;
		break;
	}

	behaviorState = Execute;
} 
void CPlane::BehaviorExecute() {
	switch (currentState) {
	case Create:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern1:
		behaviorState = Exit;
		break;

	case Idle:
		residenceTimer->Update();
		break;

	case Leave:
		m_tInfo.fY += m_fSpeed;
		LeaveCheck();
		break;
	}
} 

void CPlane::BehaviorExit() {
	switch (currentState) {
	case Create:
		currentState = Pattern1;
		break;

	case Pattern1:
		currentState = Idle;
		break;

	case Idle:
		currentState = Leave;
		break;

	case Leave:
		break;
	}

	behaviorState = Enter;
} 