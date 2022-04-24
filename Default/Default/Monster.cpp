#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Bullet.h"

CMonster::CMonster():
	m_bAIStart(false),
	m_bRunEffect(false),
	m_bEffectStep(true),
	m_effectCount(0),
	m_iScore(0) {
}

CMonster::~CMonster() {
}

int CMonster::Update() {
	BehaviorUpdate();

	Update_Rect();

	return OBJ_NOEVENT;
};

void CMonster::Late_Update() {

};


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

bool CMonster::TargetMove() {
	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);

	if (distance < 5) {
		return true;
	}

	m_tInfo.fX += (distX / distance) * m_fSpeed;
	m_tInfo.fY += (distY / distance) * m_fSpeed;

	return false;
}

void CMonster::Fire(float degree) {
	if (!m_bulletList)
		return;
	
	CObj* newBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);

	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetDirection(cosf(degree * PI / 180.f), sinf(degree * PI / 180.f));
	m_bulletList->push_back(newBullet);
}

void CMonster::DisplayInfo(HDC hDC, int _displayState) {
	if (!m_bDisplayInfo)
		return;

	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Position : (%f, %f)", m_tInfo.fX, m_tInfo.fY);
	TextOut(hDC, m_tRect.left, m_tRect.top - 20, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"위치 : %d", _displayState);
	TextOut(hDC, m_tRect.left, m_tRect.top - 40, szBuff, lstrlen(szBuff));

	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);
	swprintf_s(szBuff, L"플레이어 간 거리 : %f", distance);
	TextOut(hDC, m_tRect.left, m_tRect.top - 60, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"start TIme : %d, deta Time: %d", g_dwCurrentTime, g_dwDeltaTime);
	TextOut(hDC, m_tRect.left, m_tRect.top - 80, szBuff, lstrlen(szBuff));
}

void CMonster::RunEffect() {
	m_bRunEffect = true;
	m_bEffectStep = true;
	m_effectCount = 1;
}

void CMonster::EffectRender() {
	if (!m_bRunEffect)
		return;

	m_effectCount += m_bEffectStep ? 15 : -15;

	if (m_effectCount >= 255) {
		m_effectCount = 255 - 1;
		m_bEffectStep = false;
	}

	if (m_effectCount <= 0) {
		m_effectCount = 0;
		m_bRunEffect = false;
	}
}