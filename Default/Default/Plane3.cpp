#include "stdafx.h"
#include "Plane3.h"


CPlane3::CPlane3():
	shotTimer(nullptr) {
}


CPlane3::~CPlane3() {
	Release();
}

void CPlane3::Initialize() {
	m_tInfo.fCX = 140; //50
	m_tInfo.fCY = 90; 

	m_fSpeed = 5.f;

	m_iScore = 100;

	m_iMaxHP = 1;
	m_iHP = 1;
};

void CPlane3::Render(HDC hDC) {
	HBRUSH brush;
	HGDIOBJ OldBrush;

	EffectRender();

	brush = CreateSolidBrush(RGB(235, 10, 10));
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

void CPlane3::Release() {
	if (shotTimer)
		Safe_Delete<CTimer*>(shotTimer);
};

void CPlane3::BehaviorEnter() {
	switch (currentState) {
	case Create:
		targetPosition.x = appearPosition.x;
		targetPosition.y = appearPosition.y;
		break;

	case Pattern1: {
		shotTimer = new CTimer;
		m_tDir.fX = appearPosition.x > (WINCX * 0.5f) ? -1.f : 1.f;
		m_tDir.fY = 0;

		shotTimer->StartTimer(0.5f, [&]() {
			Fire(90);
		});
	}
		break;

	}

	behaviorState = Execute;
}
void CPlane3::BehaviorExecute() {
	switch (currentState) {
	case Create:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern1: 
		m_tInfo.fX += m_fSpeed * m_tDir.fX;
		if (m_tRect.left < 0)
			m_tDir.fX = 1;
		
		if (m_tRect.right > WINCX)
			m_tDir.fX = -1;
		
		shotTimer->Update();
		break;
	}
} 

void CPlane3::BehaviorExit() {
	switch (currentState) {
	case Create:
		currentState = Pattern1;
		break;
	}

	behaviorState = Enter;
} 