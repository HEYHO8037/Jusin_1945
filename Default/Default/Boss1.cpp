#include "stdafx.h"
#include "Boss1.h"


CBoss1::CBoss1():
	currentState(Create) {
}

CBoss1::~CBoss1() {
	Release();
}

void CBoss1::Initialize() {
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = -100.f;

	m_tInfo.fCX = 200;
	m_tInfo.fCY = 200;

	m_fSpeed = 5.f;

	m_bDisplayInfo = true;

	m_iScore = 1000;
};

void CBoss1::Render(HDC hDC) {
	HBRUSH brush, OldBrush;
	EffectRender();
	brush = CreateSolidBrush(RGB(m_effectCount, 0, 0));
	OldBrush = (HBRUSH)SelectObject(hDC, brush);

	SelectObject(hDC, brush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
	SelectObject(hDC, OldBrush);
	DeleteObject(brush);

	DisplayInfo(hDC, currentState);
};

void CBoss1::Release() {
}

void CBoss1::BehaviorEnter() {
	switch (currentState) {
	case Create:
		targetPosition.x = appearPosition.x;
		targetPosition.y = appearPosition.y;

		originPosition.x = targetPosition.x;
		originPosition.y = targetPosition.y;
		break;

	case Pattern1: {
		RunEffect();

		bossShotTimer = new CTimer;
		bossShotTimer->StartTimer(1, [&]() {
			int angle = 90;
			Fire(angle + 45);
			Fire(angle);
			Fire(angle - 45);
		});
	}
		break;

	case Pattern2:
		targetPosition.x = targetObj->Get_Info().fX;
		targetPosition.y = targetObj->Get_Info().fY;
		break;

	case Pattern2Back:
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
		break;

	case Destroy:
		m_bDead = true;
		break;
	}

	behaviorState = Execute;
}

void CBoss1::BehaviorExecute() {
	switch (currentState) {
	case Create:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern1:
		bossShotTimer->Update();
		break;

	case Pattern2:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern2Back:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Leave:
		m_tInfo.fY += m_fSpeed;
		break;
	}
}

void CBoss1::BehaviorExit() {
	switch (currentState) {
	case Create:
		currentState = Pattern1;
		break;

	case Pattern1:
		Safe_Delete<CTimer*>(bossShotTimer);
		//currentState = Pattern2;
		break;

	case Pattern2:
		currentState = Pattern2Back;
		break;

	case Pattern2Back:
		break;

	case Leave:
		break;
	}

	behaviorState = Enter;
}