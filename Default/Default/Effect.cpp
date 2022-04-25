#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect() {
}


CEffect::~CEffect() {
}

void CEffect::Initialize() {
	m_tInfo.fCX = 10;
	m_tInfo.fCY = 10;

	m_fSpeed = 8.f;
};

int CEffect::Update() {
	if (m_bDead) {
		return OBJ_DEAD;
	}

	if (m_tInfo.fCX >= m_effectEndSize.fX && m_tInfo.fCY >= m_effectEndSize.fY) {
		m_bDead = true;
	}

	m_tInfo.fCX += m_fSpeed;
	m_tInfo.fCY += m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
};

void CEffect::Late_Update() {

};

void CEffect::Render(HDC hDC) {
	HBRUSH	brush = CreateSolidBrush(RGB(255, 0, 0));
	HGDIOBJ h_old_brush = SelectObject(hDC, brush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, h_old_brush);

	DeleteObject(brush);
};

void CEffect::Release() {

};

void CEffect::CollisionEnter(CObj* _sour) {
};
