#include "stdafx.h"
#include "Boss1.h"
#include "MainGame.h"
#include <time.h>

CBoss1::CBoss1():
	currentState(Create),
	m_iShotCount(0) {
}

CBoss1::~CBoss1() {
	Release();
}

void CBoss1::Initialize() {
	m_tInfo.fCX = 400;
	m_tInfo.fCY = 380;

	m_fSpeed = 5.f;

	m_iScore = 1000;

	m_iMaxHP = 500;
	m_iHP = 500;

	bossShotTimer = new CTimer;
};

void CBoss1::Render(HDC hDC) {
	HBRUSH brush;
	HGDIOBJ OldBrush;

	EffectRender();
	
	brush = CreateSolidBrush(RGB(m_effectCount, 100, 100));
	OldBrush = SelectObject(hDC, brush);

	SelectObject(hDC, brush);
	Ellipse(hDC, m_tRect.left + 100, m_tRect.top + 20, m_tRect.right - 100, m_tRect.top + 80);
	// ?? ????
	Ellipse(hDC, m_tRect.left, m_tRect.top + 250, m_tRect.right, m_tRect.bottom - 50);
	// ????

	Rectangle(hDC, m_tRect.left + 170, m_tRect.top, m_tRect.right - 170, m_tRect.bottom);

	SelectObject(hDC, OldBrush);
	DeleteObject(brush);

	DisplayInfo(hDC, currentState);
};

void CBoss1::Release() {
	if (bossShotTimer)
		Safe_Delete<CTimer*>(bossShotTimer);
}

void CBoss1::BehaviorEnter() {
	if (!m_targetObj)
		return;

	switch (currentState) {
	case Create:
		targetPosition.x = appearPosition.x;
		targetPosition.y = appearPosition.y;

		originPosition.x = targetPosition.x;
		originPosition.y = targetPosition.y;
		break;

	case Pattern1: {

		m_iShotCount = 3;
		bossShotTimer->StartTimer(0.5f, [&]() {
			if (m_iShotCount <= 0) {
				behaviorState = Exit;
				return;
			}

			int shotAngle = 60;
			for (int i = 0; i < 7; ++i) {
				Fire(baseShotAngle + shotAngle);
				shotAngle -= 20;
			}

			--m_iShotCount;
		});
	}
		break;

	case Pattern2:
		if (m_targetObj) {
			targetPosition.x = m_targetObj->Get_Info().fX;
			targetPosition.y = m_targetObj->Get_Info().fY;
		}
		else {
			targetPosition.x = originPosition.x;
			targetPosition.y = originPosition.y;
		}
		
		break;

	case Return:
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
		break;

	case Pattern3:
		m_iShotCount = 3;
		bossShotTimer->StartTimer(1, [&]() {
			if (m_iShotCount <= 0) {
				behaviorState = Exit;
				return;
			}

			int angle = 0;
			while (angle <= 360) {
				Fire(angle);
				angle += 10;
			}

			--m_iShotCount;
		});
		break;

	case Pattern4:
		patternAngle = 0;
		bossShotTimer->StartTimer(0.01f, [&]() {
			if (patternAngle >= 360) {
				behaviorState = Exit;
			}

			Fire(patternAngle);
			patternAngle += 10;
		});

		break;

	case Idle:
		bossShotTimer->StartTimer(1, [&]() {
			behaviorState = Exit;
		});
		break;
	}

	behaviorState = Execute;
}

void CBoss1::BehaviorExecute() {
	switch (currentState) {
	case Create:
	case Pattern2:
	case Return:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern1:
	case Pattern3:
	case Pattern4:
	case Idle:
		bossShotTimer->Update();
		break;
	}
}

void CBoss1::BehaviorExit() {
	switch (currentState) {
	case Create:
	case Pattern1:
	case Pattern3:
	case Pattern4:
	case Return:
		currentState = Idle;
		break;

	case Pattern2:
		currentState = Return;
		break;

	case Idle:
		RandomPattern();
		break;
	}

	behaviorState = Enter;
}

void CBoss1::RandomPattern() {
	srand(unsigned(time(nullptr)));

	currentState = State((rand() % Pattern4) + Pattern1);
}

void CBoss1::Die() {
	CMainGame::Level += 1;
	CMainGame::BossCount += 10;
	CMainGame::KillCount = 0;
	CMainGame::bBoss = false;
}