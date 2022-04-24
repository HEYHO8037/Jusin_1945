#include "stdafx.h"
#include "Bullet.h"



CBullet::CBullet() {
}


CBullet::~CBullet() {
	Release();
}

void CBullet::Initialize() {
	m_tInfo.fCX = 10.f;	// �÷��̾� ���� ������
	m_tInfo.fCY = 10.f;	// �÷��̾� ���� ������

	m_fSpeed = 10.f;
	 
	Update_Rect();
}

int CBullet::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_tDir.fX * m_fSpeed;
	m_tInfo.fY += m_tDir.fY * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update() {
	if (m_tRect.left < 50 || m_tRect.right > WINCX - 50 || m_tRect.top < 50 || m_tRect.bottom > WINCY - 50) {
		m_bDead = true;
	}
}
//
//void CBullet::Hit() {
//	m_bDead = true;
//}

void CBullet::Render(HDC hdc) {
	HBRUSH brush;
	HPEN pen;
	pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	brush = CreateSolidBrush(RGB(0, 0, 255));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	DeleteObject(pen);
	DeleteObject(brush);
}

void CBullet::Release() {
}

void CBullet::CollisionEnter(CObj * _sour)
{
}

BULLET_TYPE CBullet::GetType() const
{
	if (this)
	{
		return m_eBulletType;
	}
	else
	{
		return BULLET_END;
	}
}

void CBullet::SetType(BULLET_TYPE eType)
{
	m_eBulletType = eType;
}
