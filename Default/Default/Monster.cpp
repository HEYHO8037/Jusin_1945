#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "Item.h"
#include "Effect.h"
#include "MainGame.h"

CMonster::CMonster():
	baseShotAngle(90),
	m_bAIStart(false),
	m_bRunEffect(false),
	m_bDisplayInfo(false),
	m_effectCount(0),
	m_iScore(0),
	effectDecreasePoint(15){
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
		bulletObj->Set_Dead();
	}
}

void CMonster::BehaviorStart(
	CObj* _targetObj, 
	std::list<CObj*>* _pBulletList, 
	std::list<CObj*>* _pItemList,
	std::list<CObj*>* _pEffectList
) {
	m_targetObj = _targetObj;
	m_bulletList = _pBulletList;
	m_itemList = _pItemList;
	m_effectList = _pEffectList;

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

void CMonster::Fire(const int _degree) {
	if (!m_bulletList)
		return;
	
	CObj* newBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, static_cast<float>(m_tRect.bottom));

	CBullet* BulletObj = dynamic_cast<CBullet*>(newBullet);
	BulletObj->SetType(MONSTER_BULLET);
	BulletObj->SetDirection(cosf(_degree * RADIAN), sinf(_degree * RADIAN));
	m_bulletList->push_back(newBullet);
}

void CMonster::DisplayInfo(HDC hDC, const int _displayState) {
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

	m_effectCount -= effectDecreasePoint;

	if (m_effectCount <= 0) {
		m_effectCount = 0;
		m_bRunEffect = false;
	}
}

void CMonster::Hit() {
	m_iHP -= 1;
	RunEffect();

	if (!m_bDead && m_iHP <= 0) {
		Die();
		CommonDie();
	}
}

void CMonster::CommonDie() {
	CItem::Create(m_itemList, this);

	CMainGame::KillCount += 1;
	CMainGame::TotalKillCount += 1;
	CMainGame::Score += (m_iScore * CMainGame::Level);

	CObj* newEffect = CAbstractFactory<CEffect>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CEffect*>(newEffect)->SetEndSize(m_tInfo.fCX, m_tInfo.fCY);
	m_effectList->push_back(newEffect);

	m_bDead = true;
	m_bAIStart = false;
}

void CMonster::Die() {
}

void CMonster::LeaveCheck() {
	if (m_tRect.left < -100 || m_tRect.right > WINCX + 100 || m_tRect.top < -100 || m_tRect.bottom > WINCY + 100) {
		m_bDead = true;
	}
} // 떠나기 패턴일때 화면밖을 벗어나는지 체크함