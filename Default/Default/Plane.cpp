#include "stdafx.h"
#include "Plane.h"


CPlane::CPlane() {
}


CPlane::~CPlane() {
	Release();
}

void CPlane::Initialize() {
	m_tInfo.fX = WINCX + 200;
	m_tInfo.fY = WINCY / 2;

	m_tInfo.fCX = 30;
	m_tInfo.fCY = 100;

	m_fSpeed = 5.f;

	BehaviorStart();
};

void CPlane::Render(HDC hDC) {
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
};

void CPlane::Release() {
};

void CPlane::BehaviorStart() {
	m_bAIStart = true;
	behaviorState = Enter;
}

void CPlane::BehaviorEnter() {
	switch (currentState) {
	case Create:
		targetPosition.x = WINCX / 2 + 200;
		targetPosition.y = WINCY / 2;

		originPosition.x = targetPosition.x;
		originPosition.y = targetPosition.y;
		break;

	case Pattern1: {
		int angle = 90;
		Fire(angle);
	}
	break;

	case Destroy:
		m_bDead = true;
		break;
	}

	behaviorState = Execute;
} // 행동 시작

void CPlane::BehaviorExecute() {
	switch (currentState) {
	case Create:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
			// 원하는 위치까지 이동
		}
		break;

	case Pattern1:
		behaviorState = Exit;
		break;

	case Leave:
		m_tInfo.fY += m_fSpeed;
		break;
	}
} // 행동 중

void CPlane::BehaviorExit() {
	switch (currentState) {
	case Create:
		currentState = Pattern1;
		break;

	case Pattern1:
		currentState = Leave;
		break;

	case Leave:
		break;
	}

	behaviorState = Enter;
} // 행동 종료