#pragma once
#include "Obj.h"
class CBullet : public CObj
{
public:
	CBullet();
	~CBullet();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual	void CollisionEnter(CObj* _sour);

public:
	BULLET_TYPE GetType() const;
	void SetType(BULLET_TYPE eType);
	void SetDirection(float _x, float _y) { m_tDir.fX = _x, m_tDir.fY = _y; };

private:
	INFO m_tDir;
	BULLET_TYPE m_eBulletType;
};

