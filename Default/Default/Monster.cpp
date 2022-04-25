#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "Item.h"
#include "MainGame.h"

CMonster::CMonster():
	m_bAIStart(false),
	m_bRunEffect(false),
	m_effectCount(0),
	m_iScore(0) {
}

CMonster::~CMonster() {
}

int CMonster::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	BehaviorUpdate();

	Update_Rect();

	return OBJ_NOEVENT;
};

void CMonster::Late_Update() {
	if (!m_bulletList)
		return;
};


void CMonster::CollisionEnter(CObj* _sour) {
	CBullet* bulletObj = dynamic_cast<CBullet*>(_sour);
	if (bulletObj && bulletObj->GetType() == PLAYER_BULLET) {
		Hit();
	}
}

void CMonster::BehaviorStart(CObj* _targetObj, std::list<CObj*>* _pBulletList, std::list<CObj*>* _pItemList) {
	targetObj = _targetObj;
	m_bulletList = _pBulletList;
	m_itemList = _pItemList;

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
	BulletObj->SetType(MONSTER_BULLET);
	BulletObj->SetDirection(cosf(degree * PI / 180.f), sinf(degree * PI / 180.f));
	m_bulletList->push_back(newBullet);
}

void CMonster::DisplayInfo(HDC hDC, int _displayState) {
	if (!m_bDisplayInfo)
		return;

	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Position : (%f, %f)", m_tInfo.fX, m_tInfo.fY);
	TextOut(hDC, m_tRect.left, m_tRect.top - 20, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"pattern : %d", _displayState);
	TextOut(hDC, m_tRect.left, m_tRect.top - 40, szBuff, lstrlen(szBuff));

	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);
	swprintf_s(szBuff, L"distance : %f", distance);
	TextOut(hDC, m_tRect.left, m_tRect.top - 60, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"start TIme : %d, deta Time: %d", g_dwCurrentTime, g_dwDeltaTime);
	TextOut(hDC, m_tRect.left, m_tRect.top - 80, szBuff, lstrlen(szBuff));
}

void CMonster::RunEffect() {
	m_bRunEffect = true;
	m_effectCount = 255;
}

void CMonster::EffectRender() {
	if (!m_bRunEffect)
		return;

	m_effectCount -= 15;

	if (m_effectCount <= 0) {
		m_effectCount = 0;
		m_bRunEffect = false;
	}
}

void CMonster::Hit() {
	m_iHP -= 1;
	RunEffect();

 	if (m_iHP <= 0)
		Die();
}

void CMonster::Die() {
	CItem::Create(m_itemList, this);

	CMainGame::killCount += 1;

	m_bDead = true;
	m_bAIStart = false;
}