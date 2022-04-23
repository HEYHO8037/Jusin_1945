#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Bullet.h"

CMonster::CMonster():
	currentState(Create),
	m_bAIStart(false) {

}


CMonster::~CMonster() {
	Release();
}


void CMonster::Initialize() {
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = -100.f;

	m_tInfo.fCX = 200;
	m_tInfo.fCY = 200;

	m_fSpeed = 5.f;

	m_bDisplayInfo = true;
};

int CMonster::Update() {
	BehaviorUpdate();

	Update_Rect();

	return OBJ_NOEVENT;
};

void CMonster::Late_Update() {

};

void CMonster::Render(HDC hDC) {
	DisplayInfo(hDC, currentState);
	
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
};

void CMonster::Release() {
}

void CMonster::BehaviorStart(CObj* _targetObj, std::list<CObj*>* _pList) {
	targetObj = _targetObj;
	m_bulletList = _pList;

	m_bAIStart = true;
	behaviorState = Enter;
}

void CMonster::BehaviorUpdate() {
	if (!m_bAIStart)
		return;

	switch (behaviorState) {
	case Enter:
		BehaviorEnter();
		break;

	case Execute:
		BehaviorExecute();
		break;

	case Exit:
		BehaviorExit();
		break;
	}
}

void CMonster::BehaviorEnter() {
	switch (currentState) {
	case Create:
		targetPosition.x = WINCX / 2;
		targetPosition.y = m_tInfo.fCY + 300;

		originPosition.x = targetPosition.x;
		originPosition.y = targetPosition.y;
		break;

	case Pattern1: {
		int angle = 90;
		Fire(angle + 45);
		Fire(angle);
		Fire(angle - 45);
	}
		break;

	case Pattern2:
		targetPosition.x = targetObj->Get_Info().fX;
		targetPosition.y = targetObj->Get_Info().fY;
		break;

	case Pattern3:
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
		break;

	case Destroy:
		m_bDead = true;
		break;
	}

	behaviorState = Execute;
} // 행동 시작

void CMonster::BehaviorExecute() {
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

	case Pattern2:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
			// 원하는 위치까지 이동
		}
		break;

	case Pattern3:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
			// 원하는 위치까지 이동
		}
		break;


	case Leave:
		m_tInfo.fY += m_fSpeed;
		break;
	}
} // 행동 중

void CMonster::BehaviorExit() {
	switch (currentState) {
	case Create:
		currentState = Pattern1;
		break;

	case Pattern1:
		currentState = Pattern2;
		break;

	case Pattern2:
		currentState = Pattern3;
		break;

	case Pattern3:
		//currentState = Leave;
		break;

	case Leave:
		break;
	}

	behaviorState = Enter;
} // 행동 종료

bool CMonster::TargetMove() {
	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);

	m_tInfo.fX += (distX / distance) * m_fSpeed;
	m_tInfo.fY += (distY / distance) * m_fSpeed;

	return distance < 30;
}

void CMonster::Fire(float degree) {
	if (!m_bulletList)
		return;
	
	CObj* newBullet = CAbstractFactory<CBullet>::Create();
	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(degree * PI / 180.f), sinf(degree * PI / 180.f));
	BulletObj->Set_pos(m_tInfo.fX, m_tInfo.fY);
	m_bulletList->push_back(newBullet);
}

void CMonster::DisplayInfo(HDC hDC, int _displayState) {
	if (!m_bDisplayInfo)
		return;

	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Position : (%f, %f)", m_tInfo.fX, m_tInfo.fY);
	TextOut(hDC, m_tRect.left, m_tRect.top - 20, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"패턴 : %d", _displayState);
	TextOut(hDC, m_tRect.left, m_tRect.top - 40, szBuff, lstrlen(szBuff));

	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);
	swprintf_s(szBuff, L"거리 : %f", distance);
	TextOut(hDC, m_tRect.left, m_tRect.top - 60, szBuff, lstrlen(szBuff));

}